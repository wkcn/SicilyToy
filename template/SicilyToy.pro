#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T11:42:12
#
#-------------------------------------------------

QT       += core
QT       += network
QMAKE_CXXFLAGS += -std=c++11

QT       += widgets

TARGET = SicilyToy

CONFIG   += static
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../ToyDef.cpp \
    Defines.cpp

HEADERS += \
    ../ToyDef.h \
    ../Defines.h \
    Defines.h
