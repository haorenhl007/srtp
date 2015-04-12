#include "transfercmd.h"
#include <config.h>
#include <QMessageBox>


TransferCmd::TransferCmd(QObject *parent, QLabel *label):
    QTcpSocket(parent)
{
    this->label = label;
    connect(this, SIGNAL(readyRead()), SLOT(read_cmd()));
    connect(this, SIGNAL(disconnected()), SLOT(deleteLater()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(socket_error(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socket_state(QAbstractSocket::SocketState)));
}

void TransferCmd::read_cmd()
{
    char *c = new char;
    if (this->getChar(c) == true)
    {
        switch (*c)
        {
        case openCommand:
            this->label->setText(tr("MatLab has been opened:)"));
            break;
        case closeCommand:
            this->label->setText(tr("MatLab has been closed:)"));
            break;
        case openSystemCommand:
            this->label->setText(tr("System has been opened"));
            break;
        case openSystemCommand2:
            this->label->setText(tr("System has been opened"));
            break;
        case connectSystemCommand:
            this->label->setText(tr("System has been connected"));
            break;
        case disconnectSystemCommand:
            this->label->setText(tr("System has been disconnected"));
            break;
        case startSystemCommand:
            this->label->setText(tr("System has been started"));
            break;
        case stopSystemCommand:
            this->label->setText(tr("System has been stopped"));
            break;
        case closeSystemCommand:
            this->label->setText(tr("System has been closed"));
            break;
        case closeSystemCommand2:
            this->label->setText(tr("System has been closed"));
            break;
        default:
            break;
        }
    }
}


void TransferCmd::socket_error(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ConnectionRefusedError"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("RemoteHostClosedError"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("HostNotFoundError"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SocketAccessError"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SocketResourceError"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SocketTimeoutError"));
        break;
    case QAbstractSocket::DatagramTooLargeError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("DatagramTooLargeError"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("NetworkError"));
        break;
    case QAbstractSocket::AddressInUseError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("AddressInUseError"));
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SocketAddressNotAvailableError"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("UnsupportedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ProxyAuthenticationRequiredError"));
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SslHandshakeFailedError"));
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("UnfinishedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ProxyConnectionRefusedError"));
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ProxyConnectionClosedError"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ProxyConnectionTimeoutError"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ProxyNotFoundError"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("ProxyProtocolError"));
        break;
    /*
    case QAbstractSocket::OperationError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("OperationError"));
        break;
    case QAbstractSocket::SslInternalError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SslInternalError"));
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("SslInvalidUserDataError"));
        break;
    case QAbstractSocket::TemporaryError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("TemporaryError"));
        break;
    */
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::information(this->label, tr("TransferCmd::TcpSocketError"), tr("UnknownSocketError"));
        break;
    default:
        break;
    }
}

void TransferCmd::socket_state(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            this->label->setText(tr("TransferCmd::TcpSocketState: Unconnected"));
            break;
        case QAbstractSocket::HostLookupState:
            this->label->setText(tr("TransferCmd::TcpSocketState: HostLookUP"));
            break;
        case QAbstractSocket::ConnectingState:
            this->label->setText(tr("TransferCmd::TcpSocketState: Connecting"));
            break;
        case QAbstractSocket::ConnectedState:
            this->label->setText(tr("TransferCmd::TcpSocketState: Connected"));
            break;
        case QAbstractSocket::BoundState:
            this->label->setText(tr("TransferCmd::TcpSocketState: Bound"));
            break;
        case QAbstractSocket::ClosingState:
            this->label->setText(tr("TransferCmd::TcpSocketState: Closing"));
            break;
        case QAbstractSocket::ListeningState:
            this->label->setText(tr("TransferCmd::TcpSocketState:: Listening"));
            break;

    }
}
