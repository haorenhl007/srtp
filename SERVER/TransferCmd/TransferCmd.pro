#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T18:55:30
#
#-------------------------------------------------

QT       += network

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Config/release/ -lConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Config/debug/ -lConfig
else:unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
