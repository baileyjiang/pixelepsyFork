#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
    , scene(new QGraphicsScene)
    , view(new QGraphicsView)
    , layout(new QVBoxLayout)
    , frame(0)
    , scale(1)
{
    view->setScene(scene);
    layout->addWidget(view);
    this->setLayout(layout);
}


void CanvasWidget::showFrame(int frame) {
    this->frame = frame;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().at(frame).get())));
}

void CanvasWidget::changeBuffer(std::shared_ptr<Buffer> buffer) {
    this->buffer = buffer;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().front().get())));
}
