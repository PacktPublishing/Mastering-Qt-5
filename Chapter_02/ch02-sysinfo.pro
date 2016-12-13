#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T16:25:01
#
#-------------------------------------------------

QT       += core gui charts
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ch02-sysinfo
TEMPLATE = app

SOURCES += main.cpp \
    MainWindow.cpp \
    SysInfo.cpp \
    CpuWidget.cpp \
    MemoryWidget.cpp \
    SysInfoWidget.cpp

HEADERS += MainWindow.h \
    SysInfo.h \
    CpuWidget.h \
    MemoryWidget.h \
    SysInfoWidget.h

windows {
    SOURCES += SysInfoWindowsImpl.cpp
    HEADERS += SysInfoWindowsImpl.h
}

linux {
    SOURCES += SysInfoLinuxImpl.cpp
    HEADERS += SysInfoLinuxImpl.h
}

macx {
    SOURCES += SysInfoMacImpl.cpp
    HEADERS += SysInfoMacImpl.h
}

FORMS    += MainWindow.ui
