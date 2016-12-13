#-------------------------------------------------
#
# Project created by QtCreator 2016-06-23T12:16:33
#
#-------------------------------------------------

QT       += core widgets

TARGET = $$qtLibraryTarget(filter-plugin-grayscale)
TEMPLATE = lib
CONFIG += plugin

SOURCES += \
    FilterGrayscale.cpp

HEADERS += \
    FilterGrayscale.h

include(../plugins-common.pri)
include(../plugins-common-opencv.pri)
