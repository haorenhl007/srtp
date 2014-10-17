#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QLabel>
#include <QTcpServer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include "tcpserver.h"

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = 0);
    ~Server();


private:
    void incomingConnection(int socketId);
    QHostAddress getIPAddress();

    QHostAddress ipAddress;
    quint16 port;
    QLabel *statusLabel;
    QPushButton *quitButton;
    QVBoxLayout *mainLayout;
    TcpServer *tcpServer;
};

#endif // SERVER_H
