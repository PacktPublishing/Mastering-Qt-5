windows {
    INCLUDEPATH += $$(OPENCV_HOME)/../../include
    LIBS += -L$$(OPENCV_HOME)/lib \
        -lopencv_core2413 \
        -lopencv_imgproc2413
}

linux {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}

macx {
    INCLUDEPATH += /usr/local/Cellar/opencv/2.4.13/include/

    LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_imgproc
}

