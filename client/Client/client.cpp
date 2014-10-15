#include "client.h"

Client::Client(QWidget *parent)
    : QDialog(parent)
{
    ipLabel = new QLabel(tr("Server IP:"));
    ipLineEdit = new QLineEdit;
    portLabel = new QLabel(tr("Port"));
    portLineEdit = new QLineEdit;

    connectBtn = new QPushButton(tr("Connect"));
    connectBtn->setEnabled(false);

    openBtn = new QPushButton(tr("Open"));
    openBtn->setEnabled(false);

    initBtn = new QPushButton(tr("Init"));
    initBtn->setEnabled(false);

    closeBtn = new QPushButton(tr("Close"));
    closeBtn->setEnabled(false);

    disconnectBtn = new QPushButton(tr("Disconnnect"));
    disconnectBtn->setEnabled(false);

    tcpSocket = new QTcpSocket;

    connect(ipLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(portLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(connectBtn, SIGNAL(clicked()), this, SLOT(connectServer()));
    connect(openBtn, SIGNAL(clicked()), this, SLOT(openMatLab()));
    connect(initBtn, SIGNAL(clicked()), this, SLOT(initMatLab()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeMatLab()));
    connect(disconnectBtn, SIGNAL(clicked()), this, SLOT(disconnectServer()));
//    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, )

    topLayout = new QHBoxLayout;
    topLayout->addWidget(ipLabel);
    topLayout->addWidget(ipLineEdit);
    topLayout->addWidget(portLabel);
    topLayout->addWidget(portLineEdit);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(connectBtn);
    bottomLayout->addWidget(openBtn);
    bottomLayout->addWidget(initBtn);
    bottomLayout->addWidget(closeBtn);
    bottomLayout->addWidget(disconnectBtn);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    setWindowTitle(tr("Client"));
}

void Client::enableConnectBtn()
{
    connectBtn->setEnabled(true);
}

void Client::connectServer()
{
    tcpSocket->connectToHost(ipLineEdit->text(), portLineEdit->text().toInt());
    //print()
}

void Client::openMatLab()
{

}

void Client::initMatLab()
{

}

void Client::closeMatLab()
{

}

void Client::disconnectServer()
{

}

Client::~Client()
{

}
