#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T16:56:11
#
#-------------------------------------------------

QT += network widgets

TARGET = TransferCmd
TEMPLATE = lib
CONFIG += c++11

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
