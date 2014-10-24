#-------------------------------------------------
#
# Project created by QtCreator 2014-10-05T20:17:33
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

SOURCES += main.cpp\
        server.cpp \
    clientsocket.cpp \
    tcpserver.cpp

HEADERS  += server.h \
    clientsocket.h \
    tcpserver.h \
    ../config.h

INCLUDEPATH += "D:\MATLAB\R2010b\extern\include"
LIBS += -L"D:\MATLAB\R2010b\extern\lib\win32\microsoft" -llibeng -llibmat -llibmx
