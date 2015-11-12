#include "timelinewidget.h"

#include <algorithm>
#include <functional>

#include <QDebug>

TimelineWidget::TimelineWidget(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout)
    , addFrame(new QPushButton("+"))
    , removeFrame(new QPushButton("-"))
    , frame(0)
{
    layout->addWidget(addFrame);
    layout->addWidget(removeFrame);

    connect(addFrame, &QPushButton::clicked, this, &TimelineWidget::insertFrameSlot);
    connect(removeFrame, &QPushButton::clicked, this, &TimelineWidget::deleteFrameSlot);

    this->setLayout(layout);
}

void TimelineWidget::updateBuffer(std::shared_ptr<Buffer> buffer) {
    // Cleanup old buttons
    for (auto it = buttons.begin(); it != buttons.end(); it++) {
        layout->removeWidget((*it).get());
    }
    buttons.clear();

    auto frames = buffer->fetchSnapshot();

    frame = std::min(frame, (int) frames.size() - 1);

    for (int i = 0; i < frames.size(); ++i) {
        std::shared_ptr<QPushButton> button = std::make_shared<QPushButton>(QString::number(i), this);

        if (i == frame) {
            button->setStyleSheet("background: red;");
        }

        layout->addWidget(button.get());
        buttons.push_back(button);


        connect(button.get(), &QPushButton::clicked, [=]() {selectFrameSlot(i);});
    }
};

int TimelineWidget::getFrameIndex() {
    return frame;
}

void TimelineWidget::selectFrameSlot(int frame) {
    this->frame = frame;
    emit selectFrame(frame);
}

void TimelineWidget::deleteFrameSlot(int frame) {
    emit deleteFrame(frame);
}

void TimelineWidget::insertFrameSlot(int frame) {
    emit insertFrame(frame);
}
