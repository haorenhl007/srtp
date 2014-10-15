#include "server.h"
#include <QList>
#include <QString>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>

Server::Server(QWidget *parent)
    : QWidget(parent)
{
    ipAddress = getIPAddress();
    port = 8000;
    statusLabel = new QLabel;
    statusLabel->setText(tr("IP: %1\nPort: %2").arg(ipAddress.toString()).arg(port));
    quitButton = new QPushButton("Quit");
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    tcpServer = new TcpServer;
    tcpServer->listen(ipAddress, port);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(quitButton);
    setLayout(mainLayout);
    setWindowTitle("Server");
}

QHostAddress Server::getIPAddress()
{
    QHostAddress ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i);
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isNull())
        ipAddress = QHostAddress(QHostAddress::LocalHost);
    return ipAddress;
}


Server::~Server()
{

}
