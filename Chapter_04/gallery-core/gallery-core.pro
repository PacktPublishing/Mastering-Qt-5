#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T15:08:40
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TARGET = gallery-core
TEMPLATE = lib
CONFIG += lib c++11

DEFINES += GALLERYCORE_LIBRARY

SOURCES += \
    AlbumModel.cpp \
    DatabaseManager.cpp \
    Album.cpp \
    Picture.cpp \
    PictureModel.cpp \
    AlbumDao.cpp \
    PictureDao.cpp

HEADERS += \
    gallery-core_global.h \
    AlbumModel.h \
    DatabaseManager.h \
    Album.h \
    Picture.h \
    PictureModel.h \
    AlbumDao.h \
    PictureDao.h
