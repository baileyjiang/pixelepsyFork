#include "toolswidget.h"

ToolsWidget::ToolsWidget(QWidget *parent)
    : QWidget(parent)
    , colorpicker(new ColorPicker)
    , layout(new QVBoxLayout)
{
    layout->addWidget(colorpicker);
    this->setLayout(layout);
}

QColor ToolsWidget::getForeground() {
    return colorpicker->getForegroundColor();
}

QColor ToolsWidget::getBackground() {
    return colorpicker->getBackgroundColor();
}
