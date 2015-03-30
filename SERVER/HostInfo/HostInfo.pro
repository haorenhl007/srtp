#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T09:56:47
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = HostInfo
TEMPLATE = lib

DEFINES += HOSTINFO_LIBRARY

SOURCES += hostinfo.cpp

HEADERS += hostinfo.h\
        hostinfo_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
