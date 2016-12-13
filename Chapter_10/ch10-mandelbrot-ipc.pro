TEMPLATE = subdirs

SUBDIRS += \
    mandelbrot-app \
    mandelbrot-worker

OTHER_FILES += \
    sdk/Message.h \
    sdk/MessageUtils.h \
    sdk/JobRequest.h \
    sdk/JobResult.h
