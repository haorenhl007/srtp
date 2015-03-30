#include "transfercmd.h"
#include <config.h>


TransferCmd::TransferCmd()
{
    QHostAddress ip = IPs().first();
    if (!ip.isNull())
    {
        this->listen(ip, tcp_port);
    }
}

void TransferCmd::incomingConnection(int socketId)
{
    TcpSocket *socket = new TcpSocket();
    socket->setSocketDescriptor(socketId);
}

void TransferCmd::test()
{
    qDebug() << "connected!" << endl;
}

TcpSocket::TcpSocket(QObject *parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
}


void TcpSocket::readClient()
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

void TcpSocket::openMatLab()
{
    //if (this->ep = engOpen(""))
    //{
        this->putChar(openCommand);
    //}

}

void TcpSocket::closeMatLab()
{
    //engClose(ep);
    this->putChar(closeCommand);
}

void TcpSocket::openSystem()
{
    //engEvalString(ep, CDWORKDIRECTORY);
    //engEvalString(ep, OPENSYSTEM);
    this->putChar(openSystemCommand);
}

void TcpSocket::connectSystem()
{
    //engEvalString(ep, CONNECTSYSTEM);
    this->putChar(connectSystemCommand);
}

void TcpSocket::disconnectSystem()
{
    //engEvalString(ep, DISCONNECTSYSTEM);
    this->putChar(connectSystemCommand);
}

void TcpSocket::startSystem()
{
    //engEvalString(ep, STARTSYSTEM);
    this->putChar(startSystemCommand);
}
void TcpSocket::stopSystem()
{
    //engEvalString(ep, STOPSYSTEM);
    this->putChar(stopSystemCommand);
}

void TcpSocket::closeSystem()
{
    //engEvalString(ep, CLOSESYSTEM);
    this->putChar(stopSystemCommand);
}