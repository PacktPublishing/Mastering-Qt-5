#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T15:09:10
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = gallery-desktop
TEMPLATE = app

SOURCES += main.cpp\
        MainWindow.cpp \
    AlbumListWidget.cpp \
    AlbumWidget.cpp \
    PictureDelegate.cpp \
    PictureWidget.cpp \
    GalleryWidget.cpp \
    ThumbnailProxyModel.cpp

HEADERS  += MainWindow.h \
    AlbumListWidget.h \
    AlbumWidget.h \
    PictureDelegate.h \
    PictureWidget.h \
    GalleryWidget.h \
    ThumbnailProxyModel.h

FORMS    += MainWindow.ui \
    AlbumListWidget.ui \
    AlbumWidget.ui \
    PictureWidget.ui \
    GalleryWidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/release/ -lgallery-core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../gallery-core/debug/ -lgallery-core
else:unix: LIBS += -L$$OUT_PWD/../gallery-core/ -lgallery-core

linux {
    target.path = $$_PRO_FILE_PWD_/../dist/desktop-linux/root/usr/bin/
    INSTALLS += target
}

INCLUDEPATH += $$PWD/../gallery-core
DEPENDPATH += $$PWD/../gallery-core

RESOURCES += \
    res/resource.qrc
