#-------------------------------------------------
#
# Project created by QtCreator 2013-11-03T12:08:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = PenguinClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    c2clistenthread.cpp \
    c2cwritethread.cpp

HEADERS += \
    c2clistenthread.h \
    c2cwritethread.h
