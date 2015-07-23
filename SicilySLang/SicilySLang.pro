#-------------------------------------------------
#
# Project created by QtCreator 2015-07-18T09:26:44
#
#-------------------------------------------------

QT       += core
QT       += network
QMAKE_CXXFLAGS +=  -std=c++11

QT       -= gui
QT       += widgets

TARGET = SicilySLang
#CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    BigInt.cpp \
    Defines.cpp \
    SBuild.cpp \
    SPar.cpp \
    SVM.cpp \
    UBigInt.cpp \
    SThread.cpp \
    MultiSLang.cpp

HEADERS += \
    BigInt.h \
    Defines.h \
    SBuild.h \
    SPar.h \
    SVM.h \
    UBigInt.h \
    Vector.h \
    SThread.h \
    MultiSLang.h
