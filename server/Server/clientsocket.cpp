#include "clientsocket.h"
#include "../../config.h"

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
    if (engClose(ep))
    {
        this->putChar(closeCommand);
    }
}
