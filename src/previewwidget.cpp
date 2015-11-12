#include "previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView)
    , layout(new QVBoxLayout)
    , frame(0)
    , scale(1)
    , timer(new QTimer)
{
    view->setScene(scene);
    layout->addWidget(view);
    this->setLayout(layout);

    connect(timer, &QTimer::timeout, this, &PreviewWidget::nextFrame);
    timer->start(66);

}

void PreviewWidget::changeBuffer(std::shared_ptr<Buffer> buffer) {

    this->buffer = buffer;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().front().get())));

}


void PreviewWidget::nextFrame() {
    auto frames = this->buffer->fetchSnapshot();
    if (frame >= (int) frames.size()) {
        frame = 0;
    }

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*(frames.at(frame).get())));

    frame++;
}
