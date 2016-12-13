QT += core network
QT -= gui

CONFIG += c++11

TARGET = ch14-hat-tips
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    HttpRequest.cpp

HEADERS += \
    HttpRequest.h \
    Person.h
