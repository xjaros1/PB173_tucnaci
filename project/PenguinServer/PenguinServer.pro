#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T12:07:52
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = PenguinServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    serverthread.cpp \
    clientsmanager.cpp \
    serverlistener.cpp \
    connectedclient.cpp \
    sharedlist.cpp

HEADERS += \
    serverthread.h \
    clientsmanager.h \
    serverlistener.h \
    connectedclient.h \
    sharedlist.h \
    config.h \
    ../messageenvelop.h
