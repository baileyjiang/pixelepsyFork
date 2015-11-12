#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mainSplit(new QSplitter)

    , canvasWidget(new CanvasWidget)
    , toolsWidget(new ToolsWidget)

    , canvasToolsSplit(new QSplitter)
    , canvasToolsContainer(new QWidget)
    , canvasToolsLayout(new QVBoxLayout)

    , previewWidget(new PreviewWidget)
    , timelineWidget(new TimelineWidget)

    , previewTimelineContainer(new QWidget)
    , previewTimelineSplit(new QSplitter)
    , previewTimelineLayout(new QVBoxLayout)
{

    // Build the canvas-tools container
    canvasToolsSplit->addWidget(toolsWidget);
    canvasToolsSplit->addWidget(canvasWidget);

    canvasToolsLayout->addWidget(canvasToolsSplit);
    canvasToolsContainer->setLayout(canvasToolsLayout);


    // Build the preview-timeline container
    previewTimelineSplit->addWidget(timelineWidget);
    previewTimelineSplit->addWidget(previewWidget);

    previewTimelineLayout->addWidget(previewTimelineSplit);
    previewTimelineContainer->setLayout(previewTimelineLayout);

    // Set up the main split
    mainSplit->setOrientation(Qt::Vertical);

    mainSplit->addWidget(canvasToolsContainer);
    mainSplit->addWidget(previewTimelineContainer);

    this->setCentralWidget(mainSplit);
    this->show();

    connect(timelineWidget, &TimelineWidget::selectFrame, this, &MainWindow::selectFrameSlot);
    connect(timelineWidget, &TimelineWidget::deleteFrame, this, &MainWindow::deleteFrameSlot);
    connect(timelineWidget, &TimelineWidget::insertFrame, this, &MainWindow::insertFrameSlot);

    connect(canvasWidget, &CanvasWidget::pointSelected, this, &MainWindow::pointSelectedSlot);

    newBuffer(std::make_shared<Buffer>(128, 128, Qt::cyan));
}

MainWindow::~MainWindow()
{

}


void MainWindow::newBuffer(std::shared_ptr<Buffer> buffer)
{
    // Change the buffer in the windows.
    this->buffer = buffer;
    previewWidget->changeBuffer(buffer);
    canvasWidget->changeBuffer(buffer);
    timelineWidget->updateBuffer(buffer);
}

void MainWindow::useTool(int x, int y)
{
    QColor fg = toolsWidget->getForeground();
    QColor bg = toolsWidget->getBackground();

    // Tool tool = toolsWidget->getTool();

    int frame = timelineWidget->getFrameIndex();
}

void MainWindow::selectFrameSlot(int frame)
{
    canvasWidget->showFrame(frame);
    timelineWidget->updateBuffer(this->buffer);
}

void MainWindow::deleteFrameSlot(int frame)
{
    buffer->deleteFrame(frame);

    previewWidget->changeBuffer(buffer);
    canvasWidget->changeBuffer(buffer);
    timelineWidget->updateBuffer(buffer);
}

void MainWindow::insertFrameSlot(int frame)
{
    buffer->insertFrame(frame);

    previewWidget->changeBuffer(buffer);
    canvasWidget->changeBuffer(buffer);
    timelineWidget->updateBuffer(buffer);
}

void MainWindow::pointSelectedSlot(QPoint point, bool isLeft)
{
    std::shared_ptr<QImage> frame = buffer->fetchFrame(timelineWidget->getFrameIndex());

    QColor color = isLeft ? toolsWidget->getForeground()
                          : toolsWidget->getBackground();


    frame->setPixel(point, color.rgba());




    previewWidget->changeBuffer(buffer);
    canvasWidget->updateBuffer(buffer, timelineWidget->getFrameIndex());
    timelineWidget->updateBuffer(buffer);
}
