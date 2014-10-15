#include "tcpserver.h"
#include "clientsocket.h"

TcpServer::TcpServer(QObject *parent) :
    QTcpServer(parent)
{
}

void TcpServer::incomingConnection(int socketId)
{
    ClientSocket *socket = new ClientSocket;
    socket->setSocketDescriptor(socketId);
}
