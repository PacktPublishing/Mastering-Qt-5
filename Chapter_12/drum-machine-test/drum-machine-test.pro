QT += core gui multimedia widgets testlib
CONFIG += c++14 console

TARGET = drum-machine-test
TEMPLATE = app

include(../drum-machine-src.pri)

DRUM_MACHINE_PATH = ../drum-machine
INCLUDEPATH += $$DRUM_MACHINE_PATH
DEPENDPATH += $$DRUM_MACHINE_PATH

SOURCES += main.cpp \
    TestJsonSerializer.cpp \
    DummySerializable.cpp \
    TestTrack.cpp \
    TestGui.cpp

HEADERS  += DummySerializable.h \
    TestJsonSerializer.h \
    TestTrack.h \
    TestGui.h
