TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    testmanager.cpp \
    connectiontest.cpp \
    catests.cpp \
    clienttest.cpp


HEADERS += \
    testmanager.h \
    minunit.h \
    connectiontest.h \
    catests.h \
    clienttest.h


