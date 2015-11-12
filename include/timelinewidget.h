#ifndef TIMELINE_H
#define TIMELINE_H

#include "buffer.h"

#include <memory>

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class TimelineWidget : public QWidget
{
        Q_OBJECT

        QHBoxLayout *layout;

        std::vector<std::shared_ptr<QPushButton>> buttons;

        int frame;


    public:
        explicit TimelineWidget(QWidget *parent = 0);

        void updateBuffer(std::shared_ptr<Buffer> buffer);

        int getFrameIndex();

    signals:
        void selectFrame(int frame);

    public slots:
        void selectFrameSlot(int frame);
};

#endif // TIMELINE_H
