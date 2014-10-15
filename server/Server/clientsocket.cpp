#include "clientsocket.h"

ClientSocket::ClientSocket(QObject *parent) :
    QTcpSocket(parent)
{
    qDebug("ok");
}
