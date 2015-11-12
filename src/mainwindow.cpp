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


    newBuffer(std::make_shared<Buffer>(128, 128, Qt::cyan));
}

MainWindow::~MainWindow()
{

}


void MainWindow::newBuffer(std::shared_ptr<Buffer> buffer)
{
    this->buffer = buffer;
    previewWidget->changeBuffer(buffer);
    timelineWidget->updateBuffer(buffer);
}

void MainWindow::useTool(int x, int y)
{
    QColor fg = toolsWidget->getForeground();
    QColor bg = toolsWidget->getBackground();

    // Tool tool = toolsWidget->getTool();

    int frame = timelineWidget->getFrameIndex();
}
