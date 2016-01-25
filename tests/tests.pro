QT       += testlib

QT       -= gui

TARGET    = qtcollectionstest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE  = app

include(../qtcollections.pri)

DEFINES += SRCDIR=\\\"$$PWD/../src\\\"

PRECOMPILED_HEADER += qtcollectionstest.h

INCLUDEPATH += $$PWD/../src

SOURCES += \
    test_main.cpp \
    orderedhashtests.cpp

HEADERS += \
    orderedhashtests.h \
    qtcollectionstest.h
