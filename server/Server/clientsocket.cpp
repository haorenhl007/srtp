#include "clientsocket.h"
#include <QDebug>
#include "engine.h"

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
            case 'a':
                openMatLab();
            case 'b':
                break;
            case 'c':
                break;
            case 'd':
                break;
            default:
                break;
        }
    }
}

void ClientSocket::openMatLab()
{
    Engine *ep;
    ep = engOpen("");
}
