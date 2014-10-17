#include "client.h"
#include <QMessageBox>

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
    statusLabel = new QLabel(tr("SocketState: Unconnected"));

    connect(ipLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(portLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(connectBtn, SIGNAL(clicked()), this, SLOT(connectServer()));
    connect(openBtn, SIGNAL(clicked()), this, SLOT(openMatLab()));
    connect(initBtn, SIGNAL(clicked()), this, SLOT(initMatLab()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeMatLab()));
    connect(disconnectBtn, SIGNAL(clicked()), this, SLOT(disconnectServer()));

    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

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
    mainLayout->addWidget(statusLabel);

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
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(displayState(QAbstractSocket::SocketState)));
}

void Client::openMatLab()
{
    if (tcpSocket->putChar('a') == false)
        QMessageBox::information(this, tr("Write Error"), tr("Error"));

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

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
        case QAbstractSocket::RemoteHostClosedError:
            QMessageBox::information(this, tr("Client Error"), tr("RemoteHostClosedError"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, tr("Client Error"), tr("ConnectionRefuseError"));
            break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, tr("Client Error"), tr("HostNotFoundError"));
            break;
        case QAbstractSocket::SocketAccessError:
            QMessageBox::information(this, tr("Client Error"), tr("SocketAccessError"));
            break;
        default:
            QMessageBox::information(this, tr("Client Error"), tr("unknown error"));
            break;
    }
}

void Client::displayState(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            statusLabel->setText(tr("SocketState: Unconnected"));
            break;
        case QAbstractSocket::HostLookupState:
            statusLabel->setText(tr("SocketState: HostLookUP"));
            break;
        case QAbstractSocket::ConnectingState:
            statusLabel->setText(tr("SocketState: Connecting"));
        case QAbstractSocket::ConnectedState:
            statusLabel->setText(tr("SocketState: Connected"));
            connectBtn->setEnabled(false);
            openBtn->setEnabled(true);
            break;
        case QAbstractSocket::BoundState:
            statusLabel->setText(tr("SocketStatus: Bound"));
            break;
        case QAbstractSocket::ClosingState:
            statusLabel->setText(tr("SocketStatus: Closing"));
            connectBtn->setEnabled(true);
            openBtn->setEnabled(false);
            break;
        case QAbstractSocket::ListeningState:
            statusLabel->setText(tr("SocketStatus:: Listening"));
            break;

    }
}


Client::~Client()
{

}
