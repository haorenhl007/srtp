#-------------------------------------------------
#
# Project created by QtCreator 2015-04-01T17:28:21
#
#-------------------------------------------------

TARGET = Config
TEMPLATE = lib

QT += network

DEFINES += CONFIG_LIBRARY

SOURCES += config.cpp

HEADERS += config.h\
        config_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
