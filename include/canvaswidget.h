#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "buffer.h"

#include <memory>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include <QPixmap>
#include <QVBoxLayout>
#include <QWidget>
#include <QPoint>


class CanvasWidget : public QGraphicsView
{
        Q_OBJECT

        std::shared_ptr<Buffer> buffer;
        QGraphicsScene *scene;
        //QGraphicsView *view;

        QVBoxLayout *layout;

        int frame;
        int scale;

    public:
        explicit CanvasWidget(QWidget *parent = 0);

        void showFrame(int frame);

        void changeBuffer(std::shared_ptr<Buffer> buffer);
        void updateBuffer(std::shared_ptr<Buffer> buffer, int frame);
        void mouseMoveEvent(QMouseEvent*);
        void mousePressEvent(QMouseEvent *);
        void mouseReleaseEvent(QMouseEvent *);
        QPoint pixelLocation(QMouseEvent*);
        bool checkPoint(QPoint);

    signals:
        void pointSelected(QPoint point, bool leftMouseButton);
    public slots:
};

#endif // CANVASWIDGET_H
