#include "clientsocket.h"
#include "../config.h"
#include <QDebug>

ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void ClientSocket::readClient()
{
    char *c = new char;
    if (this->getChar(c) == true)
    {
        switch (*c)
        {
        case openCommand:
            openMatLab();
            break;
        case closeCommand:
            closeMatLab();
            break;
        case openSystemCommand:
            openSystem();
            break;
        case connectSystemCommand:
            connectSystem();
            break;
        case disconnectSystemCommand:
            disconnectSystem();
            break;
        case startSystemCommand:
            startSystem();
            break;
        case stopSystemCommand:
            stopSystem();
            break;
        case closeSystemCommand:
            closeSystem();
            break;
        default:
            break;
        }
    }
}

void ClientSocket::openMatLab()
{
    if (ep = engOpen(""))
    {
        this->putChar(openCommand);
    }

}

void ClientSocket::closeMatLab()
{
    engClose(ep);
    this->putChar(closeCommand);
}

void ClientSocket::openSystem()
{
    engEvalString(ep, CDWORKDIRECTORY);
    engEvalString(ep, OPENSYSTEM);
    this->putChar(openSystemCommand);
}

void ClientSocket::connectSystem()
{
    engEvalString(ep, CONNECTSYSTEM);
    this->putChar(connectSystemCommand);
}

void ClientSocket::disconnectSystem()
{
    engEvalString(ep, DISCONNECTSYSTEM);
    this->putChar(connectSystemCommand);
}

void ClientSocket::startSystem()
{
    engEvalString(ep, STARTSYSTEM);
    this->putChar(startSystemCommand);
}
void ClientSocket::stopSystem()
{
    engEvalString(ep, STOPSYSTEM);
    this->putChar(stopSystemCommand);
}

void ClientSocket::closeSystem()
{
    engEvalString(ep, CLOSESYSTEM);
    this->putChar(stopSystemCommand);
}
