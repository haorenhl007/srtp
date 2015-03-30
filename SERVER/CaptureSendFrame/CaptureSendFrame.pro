#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T15:31:28
#
#-------------------------------------------------

QT += network

CONFIG += c++11

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


unix:!macx: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
