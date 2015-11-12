#ifndef TIMELINE_H
#define TIMELINE_H

#include "buffer.h"

#include <memory>

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>

class TimelineWidget : public QWidget
{
        Q_OBJECT

        QVBoxLayout *layout;

        QPushButton *addFrame;
        QPushButton *removeFrame;

        std::vector<std::shared_ptr<QPushButton>> buttons;

        int frame;


    public:
        explicit TimelineWidget(QWidget *parent = 0);

        void updateBuffer(std::shared_ptr<Buffer> buffer);

        int getFrameIndex();

    signals:
        void selectFrame(int frame);

        void deleteFrame(int frame);

        void insertFrame(int frame);

    public slots:
        void selectFrameSlot(int frame);

        void deleteFrameSlot(int frame);

        void insertFrameSlot(int frame);
};

#endif // TIMELINE_H
