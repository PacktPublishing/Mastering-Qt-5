TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-mobile

gallery-mobile.depends = gallery-core
