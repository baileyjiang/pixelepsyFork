#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "buffer.h"

#include "canvaswidget.h"
#include "toolswidget.h"
#include "previewwidget.h"
#include "timelinewidget.h"

#include <QMainWindow>
#include <QPoint>
#include <QSplitter>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
        Q_OBJECT

        QSplitter *mainSplit;


        CanvasWidget *canvasWidget;
        ToolsWidget *toolsWidget;

        QSplitter *canvasToolsSplit;
        QWidget *canvasToolsContainer;
        QVBoxLayout *canvasToolsLayout;


        PreviewWidget *previewWidget;
        TimelineWidget *timelineWidget;

        QSplitter *previewTimelineSplit;
        QWidget *previewTimelineContainer;
        QVBoxLayout *previewTimelineLayout;


        std::shared_ptr<Buffer> buffer;

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void newBuffer(std::shared_ptr<Buffer> buffer);

    public slots:
        void useTool(int x, int y);

        void selectFrameSlot(int frame);

        void deleteFrameSlot(int frame);

        void insertFrameSlot(int frame);

        void pointSelectedSlot(QPoint point, bool isLeft);

};

#endif // MAINWINDOW_H
