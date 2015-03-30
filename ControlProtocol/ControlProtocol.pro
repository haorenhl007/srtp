#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T09:34:10
#
#-------------------------------------------------

QT       -= gui
QT += network

CONFIG += c++11

TARGET = ControlProtocol
TEMPLATE = lib

DEFINES += CONTROLPROTOCOL_LIBRARY

SOURCES += controlprotocol.cpp

HEADERS += controlprotocol.h\
        controlprotocol_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
