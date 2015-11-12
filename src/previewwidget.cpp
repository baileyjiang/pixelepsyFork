#include "previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView)
    , layout(new QVBoxLayout)
    , frame(0)
    , scale(1)
    , timer(new QTimer)
    , rate(new QSlider)
{
    view->setScene(scene);
    layout->addWidget(view);
    this->setLayout(layout);

    rate->setMinimum(1);
    rate->setMaximum(100);
    rate->setValue(15);
    rate->setOrientation(Qt::Horizontal);
    layout->addWidget(rate);

    connect(timer, &QTimer::timeout, this, &PreviewWidget::nextFrame);
    connect(rate, &QSlider::sliderMoved, this, &PreviewWidget::setRate);

    timer->start(1000.0 / rate->value());
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

void PreviewWidget::setRate(int fps) {
    timer->start(1000.0 / fps);
}
