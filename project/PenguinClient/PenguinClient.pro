#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T12:08:24
#
#-------------------------------------------------

QT       += core
QT       += network widgets
QT       -= gui

TARGET = PenguinClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    c2clistenthread.cpp \
    c2cwritethread.cpp \
    clientserverthread.cpp \
    c2cudp.cpp \
    c2ctcp.cpp \
    clientbackgroundmanager.cpp \
    ../messageenvelop.cpp \
    cryptiodevice.cpp \
    cryptothreads.cpp

HEADERS += \
    c2clistenthread.h \
    c2cwritethread.h \
    clientserverthread.h \
    c2cudp.h \
    c2ctcp.h \
    clientbackgroundmanager.h \
    ../messageenvelop.h \
    cryptiodevice.h \
    cryptothreads.h

unix:!macx: LIBS += -L$$PWD/../../../../polarssl-1.2.8/library/ -lpolarssl

INCLUDEPATH += $$PWD/../../../../polarssl-1.2.8/library
DEPENDPATH += $$PWD/../../../../polarssl-1.2.8/library

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../polarssl-1.2.8/library/libpolarssl.a
