#-------------------------------------------------
#
# Project created by QtCreator 2015-04-01T15:48:06
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

#win32:CONFIG(release, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_ts300
#else:win32:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_ts300d
#
#
#win32:CONFIG(release, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_world300
#else:win32:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_world300d
#
#INCLUDEPATH += "C:/Program Files/opencv/build/include"
#DEPENDPATH += "C:/Program Files/opencv/build/include"

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv/build/x86/vc11/lib/ -lopencv_ts300
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv/build/x86/vc11/lib/ -lopencv_ts300d

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../opencv/build/x86/vc11/lib/ -lopencv_world300
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../opencv/build/x86/vc11/lib/ -lopencv_world300d

INCLUDEPATH += $$PWD/../../../opencv/build/include
DEPENDPATH += $$PWD/../../../opencv/build/include


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../Config/release/ -lConfig
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../Config/debug/ -lConfig
else:unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TransferCmd/release/ -lTransferCmd
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TransferCmd/debug/ -lTransferCmd
else:unix: LIBS += -L$$OUT_PWD/../TransferCmd/ -lTransferCmd

INCLUDEPATH += $$PWD/../TransferCmd
DEPENDPATH += $$PWD/../TransferCmd

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../TransferFrame/release/ -lTransferFrame
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../TransferFrame/debug/ -lTransferFrame
else:unix: LIBS += -L$$OUT_PWD/../TransferFrame/ -lTransferFrame

INCLUDEPATH += $$PWD/../TransferFrame
DEPENDPATH += $$PWD/../TransferFrame
