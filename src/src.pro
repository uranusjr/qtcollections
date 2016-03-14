QT      += core

greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
}

TEMPLATE = subdirs

include(../qtcollections.pri)

DEFINES += QTCOLLECTIONS_LIBRARY

unix {
    target.path = /usr/lib
    INSTALLS += target
}
