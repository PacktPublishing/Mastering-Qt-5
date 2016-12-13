QT += core gui widgets network

CONFIG += c++14

TARGET = mandelbrot-worker
TEMPLATE = app

INCLUDEPATH += $$PWD/../sdk
DEPENDPATH += $$PWD/../sdk

SOURCES += main.cpp \
    Worker.cpp \
    Job.cpp \
    WorkerWidget.cpp

HEADERS += \
    Worker.h \
    Job.h \
    WorkerWidget.h
