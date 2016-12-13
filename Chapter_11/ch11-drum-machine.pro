#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T11:36:42
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TARGET = ch11-multimedia-player
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    SoundEffectWidget.cpp \
    Track.cpp \
    PlaybackWorker.cpp \
    SoundEvent.cpp \
    JsonSerializer.cpp \
    XmlSerializer.cpp \
    BinarySerializer.cpp

HEADERS  += MainWindow.h \
    SoundEffectWidget.h \
    Track.h \
    SoundEvent.h \
    PlaybackWorker.h \
    Serializable.h \
    Serializer.h \
    JsonSerializer.h \
    XmlSerializer.h \
    BinarySerializer.h

FORMS    += MainWindow.ui

RESOURCES += \
    res/resource.qrc
