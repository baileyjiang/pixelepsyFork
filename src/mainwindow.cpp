#include "mainwindow.h"
#include "buffer.h"
#include "timelinewidget.h"
#include "previewwidget.h"
#include "canvaswidget.h"

#include <memory>
#include <vector>

#include <QImage>
#include <QTextStream>
#include <QSplitter>
#include <QWidget>
#include <QVBoxLayout>
#include <QSplitter>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QShortcut>
#include <QAction>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QInputDialog>
#include <QIODevice>
#include <QColor>
#include <QKeySequence>
#include <QRgb>


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
    , bar(new QMenuBar)
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

    this->setMenuBar(bar);
    this->createFileActions();
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
void MainWindow::createFileActions() {
    this->File = new QMenu(tr("&File"));
    this->menuBar()->addMenu(this->File);
    createAction(this->File, this->actionNew, "New", "Ctrl+N", std::bind(&MainWindow::on_actionNew_triggered, this));
    createAction(this->File, this->actionOpen, "Open", "Ctrl+O",std::bind(&MainWindow::on_actionOpen_triggered, this));
    createAction(this->File, this->actionSave, "Save", "Ctrl+S",std::bind(&MainWindow::on_actionSave_triggered, this));
    createAction(this->File, this->actionSaveAs, "Save As", "Ctrl+Shift+S", std::bind(&MainWindow::on_actionSave_As_triggered, this));
}
void MainWindow::createAction(QMenu* menu, QAction* action, const QString& text, const QString& shortcut, std::function<void()> func)
{
    action = new QAction(text, menu);
    QShortcut* shtct = new QShortcut(QKeySequence(shortcut), this);
    connect(shtct, &QShortcut::activated, this, func);
    menu->addAction(action);
    connect(action, &QAction::triggered, this, func);
}
/*
 * Menu Bar - Open Button
 */
void MainWindow::on_actionOpen_triggered()
{
    if (!fileSaved)
        newProject();
    if(cancelFlag || fileSaved){
        QFile file(QFileDialog::getOpenFileName(this, "Select a file to open...", "../", tr("Sprite Projects (*.ssp)")));

        //as long as file can be opened, proceed
        if (file.exists())
        {
            //create parameters to load from buffer
            int width;
            int height;
            int frames;

            file.open(QIODevice::ReadOnly);
            QTextStream fileStream(&file);


            fileStream >> width >> height;
            fileStream >> frames;
            int red, green, blue, alpha;
            //Buffer* buffer = new Buffer(width, height, QColor(0, 0, 0, 255));
            std::vector<std::shared_ptr<QImage>> images;
            for (int frame = 0; frame < frames; frame++) {
                    //buffer->current()->addFrame();
                    std::shared_ptr<QImage> img = std::make_shared<QImage>(width, height, QImage::Format_ARGB32);

                     for (int x = 0; x < width; x++) {
                         for (int y = 0; y < height; y++) {
                             fileStream >> red >> green >> blue >> alpha;
                             QRgb value = qRgba(red, green, blue, alpha);
                             img->setPixel(x, y, value);
                         }
                     }
                     images.push_back(img);
            }

            this->newBuffer(std::make_shared<Buffer>(images));
        }
    }
}
/*
 * Helper method which will send prompt when a new project would
 * occur before save operation
 */
void MainWindow::newProject()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Exit", "Save changes to the document before closing?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
    if (reply == QMessageBox::Yes)
        on_actionSave_triggered();
    else if (reply == QMessageBox::No)
    {
        //TODO: Reset the sprite class and window
    } else
        cancelFlag = true;
}

/*
 * Menu Bar - Save Button
 */
void MainWindow::on_actionSave_triggered()
{    // If file isn't saved yet/
    if (!fileSaved){
        // do file saving process.
        filename = fileDialog->getSaveFileName(this, tr("Save Sprite"), "untitled.ssp", tr("Sprites (*.ssp)"));
        QFile file(filename);
        if(file.open(QFile::WriteOnly | QFile::Truncate)) {
            QTextStream filestream(&file);
            filestream << buffer->toString() << endl;
            //set flag for saved file
            // fileSaved = true;
        }
    }
}

/*
 * Menu Bar - Save As Button
 */
void MainWindow::on_actionSave_As_triggered()
{
    // do file saving process.
    filename = fileDialog->getSaveFileName(this, tr("Save Sprite"), "untitled.ssp", tr("Sprites (*.ssp)"));
    QFile file(filename);
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream filestream(&file);
        filestream << buffer->toString() << endl;
        //set flag for saved file
        // fileSaved = true;
    }
}

/*
 * Menu Bar - New Button
 */
void MainWindow::on_actionNew_triggered()
{
    get_user_dimension();
}

/*
 * Populate input dialog to get dimension from the user.
 */
void MainWindow::get_user_dimension()
{
    // Will store the state whether user pressed Ok button or cancel.
    bool userChoice1;
    bool userChoice2;
    bool convertState;
    int width;
    int height;

    while (true) {
        // Ask user for the input.
        QString horizontalInput = QInputDialog::getText(this,
                                                           tr("Horizontal Dimension test"),
                                                           tr("Your dimension here"),
                                                           QLineEdit::Normal,
                                                           "",
                                                           &userChoice1);
        // If user chooses to cancel, get out of the loop.
        if (!userChoice1){
            break;
        }

        width = horizontalInput.toInt(&convertState, 10);

        // If user input cannot be converted into an integer.
        if (width <= 0 || !convertState){

            //TODO Change message box text.
            QMessageBox invalidInputPrompt;
            invalidInputPrompt.setText("wrong input @ horizontal");
            invalidInputPrompt.exec();

            continue;
        } else {

            // Obtain vertical dimension from user
            while (true) {
                QString verticalInput = QInputDialog::getText(this,
                                                               tr("Vertical Dimension test"),
                                                               tr("Your dimension here"),
                                                               QLineEdit::Normal,
                                                               "",
                                                               &userChoice2);
                // If user chooses to cancel, get out of the loop.
                if(!userChoice2){
                    break;
                }

                height = verticalInput.toInt(&convertState, 10);

                // If user input cannot be converted into an integer.
                if (height <= 0 || !convertState){

                    //TODO: Change message box text.
                    QMessageBox invalidInputPrompt;
                    invalidInputPrompt.setText("wrong input @ vertical");
                    invalidInputPrompt.exec();

                    continue;
                } else {
                    break;
                }
            }
        }
    break;
    }
    //TODO: add a scale so that the canvases aren't so small
    if(userChoice1 && userChoice2){
        add_viewer(width, height);
    }
}

void MainWindow::add_viewer(int width, int height){
    this->newBuffer(std::make_shared<Buffer>(width, height, QColor(0, 0, 0, 255)));
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
