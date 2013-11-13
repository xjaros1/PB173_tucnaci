#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T12:07:52
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

QMAKE_CXXFLAGS += -std=c++11 --coverage
 QMAKE_CXXFLAGS_DEBUG += -pg
 QMAKE_LFLAGS_DEBUG += -pg

TARGET = PenguinServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    serverthread.cpp \
    clientsmanager.cpp \
    serverlistener.cpp \
    connectedclient.cpp \
    sharedlist.cpp \
    ../messageenvelop.cpp

HEADERS += \
    serverthread.h \
    clientsmanager.h \
    serverlistener.h \
    connectedclient.h \
    sharedlist.h \
    ../messageenvelop.h

 QMAKE_CXXFLAGS_DEBUG += -pg
 QMAKE_LFLAGS_DEBUG += -pg
