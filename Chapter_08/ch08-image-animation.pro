TEMPLATE = subdirs

CONFIG += c++14

SUBDIRS += \
    image-animation \
    filter-plugin-blur \
    filter-plugin-grayscale \
    filter-plugin-original

OTHER_FILES += \
            sdk/Filter.h \
            plugins-common.pri \
            plugins-common-opencv.pri
