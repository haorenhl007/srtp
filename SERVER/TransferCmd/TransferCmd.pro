#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T08:54:52
#
#-------------------------------------------------

QT       += network

CONFIG += c++11

TARGET = TransferCmd
TEMPLATE = lib

DEFINES += TRANSFERCMD_LIBRARY

SOURCES += transfercmd.cpp

HEADERS += transfercmd.h\
        transfercmd_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix:!macx: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config