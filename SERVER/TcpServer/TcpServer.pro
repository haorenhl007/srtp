#-------------------------------------------------
#
# Project created by QtCreator 2015-04-02T20:57:18
#
#-------------------------------------------------

QT       += network

TARGET = TcpServer
TEMPLATE = lib
CONFIG += c++11

DEFINES += TCPSERVER_LIBRARY

SOURCES += tcpserver.cpp

HEADERS += tcpserver.h\
        tcpserver_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Config/release/ -lConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Config/debug/ -lConfig
else:unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
