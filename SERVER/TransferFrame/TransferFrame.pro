#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T18:55:56
#
#-------------------------------------------------

QT       += network

TARGET = TransferFrame
TEMPLATE = lib
CONFIG += c++11

DEFINES += TRANSFERFRAME_LIBRARY

SOURCES += transferframe.cpp

HEADERS += transferframe.h\
        transferframe_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Config/release/ -lConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Config/debug/ -lConfig
else:unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv
