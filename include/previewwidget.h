#ifndef PREVIEW_H
#define PREVIEW_H

#include "buffer.h"

#include <memory>

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPixmap>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

class PreviewWidget : public QWidget
{
        Q_OBJECT

        std::shared_ptr<Buffer> buffer;

        QGraphicsScene *scene;
        QGraphicsView *view;

        QVBoxLayout *layout;

        int frame;
        int scale;

        QTimer *timer;


    public:
        explicit PreviewWidget(QWidget *parent = 0);

        void changeBuffer(std::shared_ptr<Buffer> buffer);

    signals:

    public slots:
        void nextFrame();
};

#endif // PREVIEW_H
