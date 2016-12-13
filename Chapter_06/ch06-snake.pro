TEMPLATE = app

QT += qml quick 3dcore 3drender 3dquick 3dinput 3dextras
CONFIG += c++11

SOURCES += main.cpp

RESOURCES += \
    snake.qrc

HEADERS +=

DISTFILES += \
    test-shader.vsh \
    test-shader.fsh

target.files = ch06-snake
target.path = /home/pi
INSTALLS += target
