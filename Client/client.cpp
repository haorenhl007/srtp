#include "client.h"
#include "../config.h"

#include <QMessageBox>

Client::Client(QWidget *parent)
    : QWidget(parent)
{
    ipLabel = new QLabel(tr("Server IP:"));
    ipLineEdit = new QLineEdit;
    portLabel = new QLabel(tr("Port"));
    portLineEdit = new QLineEdit;
    
    connectBtn = new QPushButton(tr("Connect"));
    btnList.append(connectBtn);
    connectBtn->setEnabled(true);


    openBtn = new QPushButton(tr("Open"));
    btnList.append(openBtn);
    openBtn->setEnabled(true);

    closeBtn = new QPushButton(tr("Close"));
    btnList.append(closeBtn);
    closeBtn->setEnabled(true);

    disconnectBtn = new QPushButton(tr("Disconnnect"));
    btnList.append(disconnectBtn);
    disconnectBtn->setEnabled(true);

    openSystemBtn = new QPushButton(tr("Open System"));
    btnList.append(openSystemBtn);
    openSystemBtn->setEnabled(true);

    connectSystemBtn = new QPushButton(tr("Connect System"));
    btnList.append(connectSystemBtn);
    connectSystemBtn->setEnabled(true);

    disconnectSystemBtn = new QPushButton(tr("Disconnect System"));
    btnList.append(disconnectSystemBtn);
    disconnectSystemBtn->setEnabled(true);

    startSystemBtn = new QPushButton(tr("Start System"));
    btnList.append(startSystemBtn);
    startSystemBtn->setEnabled(true);

    stopSystemBtn = new QPushButton(tr("Stop System"));
    btnList.append(stopSystemBtn);
    stopSystemBtn->setEnabled(true);

    closeSystemBtn = new QPushButton(tr("Close System"));
    btnList.append(closeSystemBtn);
    closeSystemBtn->setEnabled(true);

    tcpSocket = new QTcpSocket;
    statusLabel = new QLabel(tr("SocketState: Unconnected"));

    connect(ipLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(portLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(connectBtn, SIGNAL(clicked()), this, SLOT(connectServer()));
    connect(openBtn, SIGNAL(clicked()), this, SLOT(openMatLab()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeMatLab()));
    connect(disconnectBtn, SIGNAL(clicked()), this, SLOT(disconnectServer()));
    connect(openSystemBtn, SIGNAL(clicked()), this, SLOT(openSystem()));
    connect(connectSystemBtn, SIGNAL(clicked()), this, SLOT(connectSystem()));
    connect(disconnectSystemBtn, SIGNAL(clicked()), this, SLOT(disconnectSystem()));
    connect(startSystemBtn, SIGNAL(clicked()), this, SLOT(startSystem()));
    connect(stopSystemBtn, SIGNAL(clicked()), this, SLOT(stopSystme()));
    connect(closeSystemBtn, SIGNAL(clicked()), this, SLOT(closeSystem()));


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

    mediumLayout = new QHBoxLayout;
    mediumLayout->addWidget(connectBtn);
    mediumLayout->addWidget(openBtn);
    mediumLayout->addWidget(closeBtn);
    mediumLayout->addWidget(disconnectBtn);

    bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(openSystemBtn);
    bottomLayout->addWidget(connectSystemBtn);
    bottomLayout->addWidget(disconnectSystemBtn);
    bottomLayout->addWidget(startSystemBtn);
    bottomLayout->addWidget(stopSystemBtn);
    bottomLayout->addWidget(closeSystemBtn);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(mediumLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addWidget(statusLabel);

    setLayout(mainLayout);
    setWindowTitle(tr("Client"));
}

void Client::enableConnectBtn()
{
}

void Client::setBtnStatus(quint16 enableStatus, quint16 defaultStatus)
{
    QList<QPushButton*>::const_iterator i = btnList.end() - 1;
    do
    {
        if (enableStatus % 2 == 1)
        {
            (*i)->setEnabled(true);
        }
        else
        {
           (*i)->setEnabled(false);
        }
        if (defaultStatus % 2 == 1)
        {
            (*i)->setDefault(true);
        }
        else
        {
            (*i)->setDefault(false);
        }
        i = i - 1;
    } while ((enableStatus /= 2) > 0 || i >= btnList.begin());
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
        statusLabel->setText(tr("MatLab is starting"));
    }
}


void Client::closeMatLab()
{

    if (tcpSocket->putChar(closeCommand) == false)
    {

        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("MatLab is closing"));
    }
}

void Client::disconnectServer()
{
    tcpSocket->close();
}

void Client::openSystem()
{
    if (tcpSocket->putChar(openSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("System is opening"));
    }
}

void Client::connectSystem()
{
    if (tcpSocket->putChar(connectSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("Connecting to System"));
    }

}

void Client::disconnectSystem()
{
    if (tcpSocket->putChar(disconnectSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("Disconnecting to system"));
    }

}

void Client::startSystem()
{
    if (tcpSocket->putChar(startSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("System is strarting"));
    }

}

void Client::stopSystme()
{
    if (tcpSocket->putChar(stopSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("System is stopping"));
    }

}

void Client::closeSystem()
{
    if (tcpSocket->putChar(closeSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        statusLabel->setText(tr("System is closing"));
    }

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
            break;
        case QAbstractSocket::HostLookupState:
            statusLabel->setText(tr("SocketState: HostLookUP"));
            break;
        case QAbstractSocket::ConnectingState:
            statusLabel->setText(tr("SocketState: Connecting"));
            break;
        case QAbstractSocket::ConnectedState:
            statusLabel->setText(tr("SocketState: Connected"));
            break;
        case QAbstractSocket::BoundState:
            statusLabel->setText(tr("SocketStatus: Bound"));
            break;
        case QAbstractSocket::ClosingState:
            statusLabel->setText(tr("SocketStatus: Closing"));
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
            statusLabel->setText(tr("MatLab has been opened:)"));
            break;
        case closeCommand:
            statusLabel->setText(tr("MatLab has been closed:)"));
            break;
        case openSystemCommand:
            statusLabel->setText(tr("System has been opened"));
            break;
        case connectSystemCommand:
            statusLabel->setText(tr("System has been connected"));
            break;
        case disconnectSystemCommand:
            statusLabel->setText(tr("System has been disconnected"));
            break;
        case startSystemCommand:
            statusLabel->setText(tr("System has been started"));
            break;
        case stopSystemCommand:
            statusLabel->setText(tr("System has been stopped"));
            break;
        case closeSystemCommand:
            statusLabel->setText(tr("System has been closed"));
            break;
        default:
            break;
        }
    }
}


Client::~Client()
{

}
