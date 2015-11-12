#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout)
    , label(new QLabel("Canvas"))
{
    layout->addWidget(label);
    label->show();

    this->setLayout(layout);
}
