TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    client.cpp \
    server.cpp \
    ca.cpp

HEADERS += \
    client.h \
    config.h \
    server.h \
    ca.h

