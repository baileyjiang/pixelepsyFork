#include "previewwidget.h"

PreviewWidget::PreviewWidget(QWidget *parent)
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

void PreviewWidget::changeBuffer(std::shared_ptr<Buffer> buffer) {
    this->buffer = buffer;

    scene->clear();
    scene->addPixmap(QPixmap::fromImage(
                         *(this->buffer->fetchSnapshot().front().get())));
}
