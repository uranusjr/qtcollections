QT      += core gui

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    CONFIG += c++11
}

TARGET   = qtcollections
TEMPLATE = lib

include(../qtcollections.pri)

DEFINES += QTCOLLECTIONS_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}
