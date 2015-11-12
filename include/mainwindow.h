#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "buffer.h"

#include "canvaswidget.h"
#include "toolswidget.h"
#include "previewwidget.h"
#include "timelinewidget.h"

#include <QMainWindow>
#include <QSplitter>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QShortcut>
#include <QInputDialog>
#include <QMessageBox>
#include <QColor>
#include <QSaveFile>
#include <QTextStream>
#include <QImage>

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
        void createFileActions();
        void createAction(QMenu*, QAction*, const QString&, const QString&, std::function<void()> func);
        void newProject();
    private:
        QFileDialog* fileDialog;
        QString filename;
        QShortcut* newFileShortcut;
        QShortcut* openFileShortcut;
        QShortcut* saveFileShortcut;
        QShortcut* saveAsShortcut;
        QInputDialog* newFileVerticalInput;
        QInputDialog* newFileHorizontalInput;
        QSaveFile save;
        bool fileSaved;
        bool cancelFlag;
        QMenu* File;
        QAction* actionNew;
        QAction* actionOpen;
        QAction* actionSave;
        QAction* actionSaveAs;
        QMenuBar* bar;
        QImage* image;

    private slots:
        void useTool(int x, int y);
        void on_actionOpen_triggered();
        void on_actionSave_triggered();
        void on_actionSave_As_triggered();
        void on_actionNew_triggered();
        void get_user_dimension();
        void add_viewer(int horiz, int vert);
};

#endif // MAINWINDOW_H
