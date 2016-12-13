#-------------------------------------------------
#
# Project created by QtCreator 2016-07-18T15:29:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14
TARGET = ch09-mandelbrot-threadpool
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    MandelbrotWidget.cpp \
    MandelbrotCalculator.cpp \
    Job.cpp

HEADERS  += MainWindow.h \
    MandelbrotWidget.h \
    MandelbrotCalculator.h \
    JobResult.h \
    Job.h

FORMS    += MainWindow.ui
