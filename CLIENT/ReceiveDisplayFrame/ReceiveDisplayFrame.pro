#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T15:57:45
#
#-------------------------------------------------

QT += network widgets

TARGET = ReceiveDisplayFrame
TEMPLATE = lib
CONFIG += c++11

DEFINES += RECEIVEDISPLAYFRAME_LIBRARY

SOURCES += receivedisplayframe.cpp

HEADERS += receivedisplayframe.h\
        receivedisplayframe_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
