-------------------------------------------------
#
# Project created by QtCreator 2016-06-09T15:46:15
#
#-------------------------------------------------

QT += widgets uiplugin
CONFIG += plugin
CONFIG += c++14
TEMPLATE = lib
DEFINES += FILTERPLUGINDESIGNER_LIBRARY

TARGET = $$qtLibraryTarget($$TARGET)
INSTALLS += target

windows {
    target.path = $$(QTDIR)/../../Tools/QtCreator/bin/plugins/designer

    debug:target_lib.files = $$OUT_PWD/debug/$${TARGET}.lib
    release:target_lib.files = $$OUT_PWD/release/$${TARGET}.lib
    target_lib.path = $$(QTDIR)/../../Tools/QtCreator/bin/plugins/designer
    INSTALLS += target_lib

    INCLUDEPATH += $$(OPENCV_HOME)/../../include
    LIBS += -L$$(OPENCV_HOME)/lib
        -lopencv_core2413
        -lopencv_imgproc2413
}

linux {
    target.path = $$(QTDIR)/../../Tools/QtCreator/lib/Qt/plugins/designer/

    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

macx {
    target.path = "$$(QTDIR)/../../Qt Creator.app/Contents/PlugIns/designer/"
    target_lib.files = $$OUT_PWD/lib$${TARGET}.dylib
    target_lib.path = "$$(QTDIR)/../../Qt Creator.app/Contents/PlugIns/designer/"
    INSTALLS += target_lib

    INCLUDEPATH += /usr/local/Cellar/opencv/2.4.13/include/

    LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgproc
}

SOURCES += FilterPluginDesigner.cpp \
    FilterWidget.cpp \
    Filter.cpp \
    FilterBlur.cpp \
    FilterOriginal.cpp \
    FilterGrayscale.cpp

HEADERS += FilterPluginDesigner.h\
    FilterWidget.h \
    Filter.h \
    FilterBlur.h \
    FilterOriginal.h \
    FilterGrayscale.h \
    filter-plugin-designer_global.h

FORMS += \
    FilterWidget.ui

RESOURCES += \
    filter-plugin-designer.qrc
