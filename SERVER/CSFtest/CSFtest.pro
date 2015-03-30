#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T16:52:06
#
#-------------------------------------------------

QT       += testlib network

CONFIG += c++11

TARGET = tst_csftesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_csftesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx: LIBS += -L$$OUT_PWD/../CaptureSendFrame/ -lCaptureSendFrame

INCLUDEPATH += $$PWD/../CaptureSendFrame
DEPENDPATH += $$PWD/../CaptureSendFrame
