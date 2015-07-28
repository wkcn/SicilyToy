#-------------------------------------------------
#
# Project created by QtCreator 2015-07-17T13:35:06
#
#-------------------------------------------------

QT       += core
QT       += network
QMAKE_CXXFLAGS += -std=c++11

QT       += widgets


TARGET = SicilyTranslator

#CONFIG += static
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Trans.cpp \
    ../ToyDef.cpp

HEADERS += \
    Trans.h \
    ../ToyDef.h

#编译时需要修改Python库目录
win32: LIBS += -L$$PWD/../../../App/Python27/libs/ -lpython27

win32: INCLUDEPATH += $$PWD/../../../App/Python27/include
win32: DEPENDPATH += $$PWD/../../../App/Python27/include

linux: INCLUDEPATH += -I /usr/include/python2.7/
linux: LIBS += -L /usr/lib/python2.7/ -lpython2.7
