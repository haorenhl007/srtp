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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Config/release/ -lConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Config/debug/ -lConfig
else:unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
