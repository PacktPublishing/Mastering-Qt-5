#-------------------------------------------------
#
# Project created by QtCreator 2016-06-23T12:14:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image-animation
TEMPLATE = app

INCLUDEPATH += $$PWD/../sdk
DEPENDPATH += $$PWD/../sdk

SOURCES += \
    main.cpp\
    MainWindow.cpp \
    FilterWidget.cpp \
    FilterLoader.cpp

HEADERS += \
    MainWindow.h \
    FilterWidget.h \
    FilterLoader.h

FORMS += \
    MainWindow.ui \
    FilterWidget.ui

RESOURCES += \
    image-animation.qrc
