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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ReceiveDisplayFrame/release/ -lReceiveDisplayFrame
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ReceiveDisplayFrame/debug/ -lReceiveDisplayFrame
else:unix: LIBS += -L$$OUT_PWD/../ReceiveDisplayFrame/ -lReceiveDisplayFrame

INCLUDEPATH += $$PWD/../ReceiveDisplayFrame
DEPENDPATH += $$PWD/../ReceiveDisplayFrame

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TransferCmd/release/ -lTransferCmd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TransferCmd/debug/ -lTransferCmd
else:unix: LIBS += -L$$OUT_PWD/../TransferCmd/ -lTransferCmd

INCLUDEPATH += $$PWD/../TransferCmd
DEPENDPATH += $$PWD/../TransferCmd

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Config/release/ -lConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Config/debug/ -lConfig
else:unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config
