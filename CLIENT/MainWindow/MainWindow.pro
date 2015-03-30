#-------------------------------------------------
#
# Project created by QtCreator 2015-03-30T16:57:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainWindow
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


unix:!macx: LIBS += -L$$OUT_PWD/../TransferCmd/ -lTransferCmd

INCLUDEPATH += $$PWD/../TransferCmd
DEPENDPATH += $$PWD/../TransferCmd


unix:!macx: LIBS += -L$$OUT_PWD/../ReceiveDisplayFrame/ -lReceiveDisplayFrame

INCLUDEPATH += $$PWD/../ReceiveDisplayFrame
DEPENDPATH += $$PWD/../ReceiveDisplayFrame


unix:!macx: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
