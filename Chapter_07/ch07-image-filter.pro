TEMPLATE = subdirs

SUBDIRS += \
    image-filter \
    filter-plugin-designer

image-filter.depends = filter-plugin-designer
