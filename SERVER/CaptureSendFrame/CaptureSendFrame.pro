#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T15:31:28
#
#-------------------------------------------------

QT += network widgets

CONFIG += c++11

TARGET = CaptureSendFrame
TEMPLATE = lib

DEFINES += CAPTURESENDFRAME_LIBRARY

SOURCES += capturesendframe.cpp

HEADERS += capturesendframe.h\
        capturesendframe_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv


unix: LIBS += -L$$OUT_PWD/../../Config/ -lConfig

INCLUDEPATH += $$PWD/../../Config
DEPENDPATH += $$PWD/../../Config

win32:CONFIG(release, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_ts300
else:win32:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_ts300d

win32:CONFIG(release, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_world300
else:win32:CONFIG(debug, debug|release): LIBS += -L"C:/Program Files/opencv/build/x86/vc11/lib" -lopencv_world300d

INCLUDEPATH += "C:/Program Files/opencv/sources/include"
DEPENDPATH += "C:/Program Files/opencv/sources/include"
