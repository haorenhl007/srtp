#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T10:32:12
#
#-------------------------------------------------

QT       += network testlib

TARGET = tst_cptesttest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_cptesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"


unix:!macx: LIBS += -L$$OUT_PWD/../ControlProtocol/ -lControlProtocol

INCLUDEPATH += $$PWD/../ControlProtocol
DEPENDPATH += $$PWD/../ControlProtocol
