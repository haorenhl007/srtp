#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T15:31:28
#
#-------------------------------------------------

CONFIG += c++11
QT += network
TARGET = CaptureSendFrame
TEMPLATE = lib

DEFINES += CAPTURESENDFRAME_LIBRARY

SOURCES += capturesendframe.cpp

HEADERS += capturesendframe.h\
        capturesendframe_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
