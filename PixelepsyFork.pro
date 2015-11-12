#-------------------------------------------------
#
# Project created by QtCreator 2015-11-12T03:46:08
#
#-------------------------------------------------

QT       += core gui testlib
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PixelepsyFork
TEMPLATE = app

INCLUDEPATH += include


SOURCES += src/main.cpp\
           src/mainwindow.cpp \
           src/buffer.cpp \
           src/canvaswidget.cpp \
           src/toolswidget.cpp \
           src/previewwidget.cpp \
           src/timelinewidget.cpp \
    src/colorpicker.cpp \
    src/tool.cpp

HEADERS += include/mainwindow.h \
           include/buffer.h \
           include/canvaswidget.h \
           include/toolswidget.h \
           include/previewwidget.h \
           include/timelinewidget.h \
    include/colorpicker.h \
    include/tool.h
