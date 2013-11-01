#-------------------------------------------------
#
# Project created by QtCreator 2013-11-01T13:18:24
#
#-------------------------------------------------

QT       += core
QT       += network widgets

QT       -= gui

TARGET = myClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


HEADERS       = blockingclient.h \
                fortunethread.h
SOURCES       = blockingclient.cpp \
                main.cpp \
                fortunethread.cpp
