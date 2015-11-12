#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "buffer.h"

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>

class CanvasWidget : public QWidget
{
        Q_OBJECT

        std::shared_ptr<Buffer> buffer;

        QGraphicsScene *scene;
        QGraphicsView *view;

        QVBoxLayout *layout;

        int frame;
        int scale;

    public:
        explicit CanvasWidget(QWidget *parent = 0);

        void showFrame(int frame);

        void changeBuffer(std::shared_ptr<Buffer> buffer);

    signals:

    public slots:
};

#endif // CANVASWIDGET_H
