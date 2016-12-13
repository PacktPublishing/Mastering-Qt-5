#-------------------------------------------------
#
# Project created by QtCreator 2016-08-09T10:55:27
#
#-------------------------------------------------

QT       += core gui widgets network

CONFIG += c++14

TARGET = mandelbrot-app
TEMPLATE = app

INCLUDEPATH += $$PWD/../sdk
DEPENDPATH += $$PWD/../sdk

SOURCES += main.cpp\
        MainWindow.cpp \
    MandelbrotCalculator.cpp \
    MandelbrotWidget.cpp \
    WorkerClient.cpp

HEADERS  += MainWindow.h \
    MandelbrotCalculator.h \
    MandelbrotWidget.h \
    WorkerClient.h

FORMS    += MainWindow.ui
