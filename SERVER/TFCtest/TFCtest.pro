#-------------------------------------------------
#
# Project created by QtCreator 2015-03-27T08:55:35
#
#-------------------------------------------------

QT       += network testlib

TARGET = tst_tfctesttest
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_tfctesttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx: LIBS += -L$$OUT_PWD/../TransferCmd/ -lTransferCmd

INCLUDEPATH += $$PWD/../TransferCmd
DEPENDPATH += $$PWD/../TransferCmd

unix:!macx: LIBS += -L$$OUT_PWD/../CaptureSendFrame/ -lCaptureSendFrame

INCLUDEPATH += $$PWD/../CaptureSendFrame
DEPENDPATH += $$PWD/../CaptureSendFrame

unix:!macx: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
