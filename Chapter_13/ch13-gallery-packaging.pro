TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-desktop \
    gallery-mobile

gallery-desktop.depends = gallery-core
gallery-mobile.depends = gallery-core
