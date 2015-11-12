#ifndef TOOLSWIDGET_H
#define TOOLSWIDGET_H

#include "colorpicker.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class ToolsWidget : public QWidget
{
        Q_OBJECT

        ColorPicker *colorpicker;

        QVBoxLayout *layout;
    public:
        explicit ToolsWidget(QWidget *parent = 0);

        QColor getForeground();
        QColor getBackground();

    signals:

    public slots:
};

#endif // TOOLSWIDGET_H
