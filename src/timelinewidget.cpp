#include "timelinewidget.h"

#include <algorithm>
#include <functional>

#include <QDebug>

TimelineWidget::TimelineWidget(QWidget *parent)
    : QWidget(parent)
    , layout(new QHBoxLayout)
    , frame(0)
{
    this->setLayout(layout);
}

void TimelineWidget::updateBuffer(std::shared_ptr<Buffer> buffer) {
    // Cleanup old buttons
    for (auto it = buttons.begin(); it != buttons.end(); it++) {
        layout->removeWidget((*it).get());
    }
    buttons.clear();

    auto frames = buffer->fetchSnapshot();

    for (int i = 0; i < frames.size(); ++i) {
        std::shared_ptr<QPushButton> button = std::make_shared<QPushButton>(QString::number(i), this);
        layout->addWidget(button.get());
        buttons.push_back(button);
    }
};

int TimelineWidget::getFrameIndex() {
    return frame;
}

void TimelineWidget::selectFrameSlot(int frame) {
    this->frame = frame;
    emit selectFrame(frame);
}
