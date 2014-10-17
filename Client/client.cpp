#include "client.h"
#include "../config.h"

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
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(readServer()));

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
    connectBtn->setDefault(true);
    connectBtn->setEnabled(true);
}

void Client::connectServer()
{
    tcpSocket->connectToHost(ipLineEdit->text(), portLineEdit->text().toInt());
}

void Client::openMatLab()
{
    if (tcpSocket->putChar(openCommand) == false)
    {

        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        openBtn->setEnabled(false);
        disconnectBtn->setEnabled(false);
        statusLabel->setText(tr("MatLab is starting"));
    }
}

void Client::initMatLab()
{

}

void Client::closeMatLab()
{

    if (tcpSocket->putChar(closeCommand) == false)
    {

        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        closeBtn->setEnabled(false);
        statusLabel->setText(tr("MatLab is closing"));
    }
}

void Client::disconnectServer()
{
    tcpSocket->close();
    disconnectBtn->setEnabled(false);
    connectBtn->setDefault(true);
    connectBtn->setEnabled(true);
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("socketError"), tr("ConnectionRefusedError"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this, tr("socketError"), tr("RemoteHostClosedError"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("socketError"), tr("HostNotFoundError"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::information(this, tr("socketError"), tr("SocketAccessError"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::information(this, tr("socketError"), tr("SocketResourceError"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::information(this, tr("socketError"), tr("SocketTimeoutError"));
        break;
    case QAbstractSocket::DatagramTooLargeError:
        QMessageBox::information(this, tr("socketError"), tr("DatagramTooLargeError"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::information(this, tr("socketError"), tr("NetworkError"));
        break;
    case QAbstractSocket::AddressInUseError:
        QMessageBox::information(this, tr("socketError"), tr("AddressInUseError"));
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        QMessageBox::information(this, tr("socketError"), tr("SocketAddressNotAvailableError"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::information(this, tr("socketError"), tr("UnsupportedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyAuthenticationRequiredError"));
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        QMessageBox::information(this, tr("socketError"), tr("SslHandshakeFailedError"));
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        QMessageBox::information(this, tr("socketError"), tr("UnfinishedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyConnectionRefusedError"));
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyConnectionClosedError"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyConnectionTimeoutError"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyNotFoundError"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyProtocolError"));
        break;
    /*
    case QAbstractSocket::OperationError:
        QMessageBox::information(this, tr("socketError"), tr("OperationError"));
        break;
    case QAbstractSocket::SslInternalError:
        QMessageBox::information(this, tr("socketError"), tr("SslInternalError"));
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        QMessageBox::information(this, tr("socketError"), tr("SslInvalidUserDataError"));
        break;
    case QAbstractSocket::TemporaryError:
        QMessageBox::information(this, tr("socketError"), tr("TemporaryError"));
        break;
    */
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::information(this, tr("socketError"), tr("UnknownSocketError"));
        break;
    default:
        break;
    }
}

void Client::displayState(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            statusLabel->setText(tr("SocketState: Unconnected"));
            connectBtn->setDefault(true);
            connectBtn->setEnabled(true);
            break;
        case QAbstractSocket::HostLookupState:
            statusLabel->setText(tr("SocketState: HostLookUP"));
            break;
        case QAbstractSocket::ConnectingState:
            statusLabel->setText(tr("SocketState: Connecting"));
        case QAbstractSocket::ConnectedState:
            statusLabel->setText(tr("SocketState: Connected"));
            connectBtn->setEnabled(false);
            openBtn->setDefault(true);
            openBtn->setEnabled(true);
            break;
        case QAbstractSocket::BoundState:
            statusLabel->setText(tr("SocketStatus: Bound"));
            break;
        case QAbstractSocket::ClosingState:
            statusLabel->setText(tr("SocketStatus: Closing"));
            openBtn->setEnabled(false);
            break;
        case QAbstractSocket::ListeningState:
            statusLabel->setText(tr("SocketStatus:: Listening"));
            break;

    }
}


void Client::readServer()
{
    char *c = new char;
    if (tcpSocket->getChar(c) == true)
    {
        switch (*c)
        {
        case openCommand:
            openBtn->setEnabled(false);
            closeBtn->setDefault(true);
            closeBtn->setEnabled(true);
            statusLabel->setText(tr("MatLab has been opened:)"));
            break;
        case closeCommand:
            closeBtn->setEnabled(false);
            disconnectBtn->setDefault(true);
            disconnectBtn->setEnabled(true);
            openBtn->setEnabled(true);
            statusLabel->setText(tr("MatLab has been closed:)"));
            break;
        default:
            break;
        }
    }
}


Client::~Client()
{

}
