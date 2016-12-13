TEMPLATE = subdirs

SUBDIRS += \
    gallery-core \
    gallery-desktop

gallery-desktop.depends = gallery-core
