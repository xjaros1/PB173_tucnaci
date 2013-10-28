#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T00:59:33
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = MultiThreadedQTcpServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    mythread.cpp \
    myserver.cpp

HEADERS += \
    mythread.h \
    myserver.h
