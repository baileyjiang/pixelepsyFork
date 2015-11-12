#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class CanvasWidget : public QWidget
{
        Q_OBJECT

        QVBoxLayout *layout;
        QLabel *label;

    public:
        explicit CanvasWidget(QWidget *parent = 0);

    signals:

    public slots:
};

#endif // CANVASWIDGET_H
