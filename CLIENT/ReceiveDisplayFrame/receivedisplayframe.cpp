#include "receivedisplayframe.h"
#include <config.h>
#include <QMessageBox>

ReceiveDisplayFrame::ReceiveDisplayFrame(QObject *parent, int buffersize):
    QObject(parent)
{
    this->img_queue = new QQueue<QImage>();
    this->receive = new QSemaphore(buffersize);
    this->display = new QSemaphore(0);
}

UdpSocket::UdpSocket(QObject *parent, ReceiveDisplayFrame *rdf, QLabel *label):
    QUdpSocket(parent)
{
    this->rdf = rdf;
    this->label = label;
    this->bind(udp_port);

    connect(this, SIGNAL(readyRead()), this, SLOT(receive_frame()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),//这些显示状态的代码重复了, 可以用一个类继承QAbstractSocket, 然后RDF和TransferCmd在继承这个类, 但是既然它们两个已经作为单独的lib了, 再整理不麻烦了.
            this, SLOT(socket_error(QAbstractSocket::SocketError)));
    connect(this, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(socket_state(QAbstractSocket::SocketState)));
}


void UdpSocket::receive_frame()
{
    QByteArray ba;
    while (this->hasPendingDatagrams());
    {
        ba.resize(this->pendingDatagramSize());
        this->read(ba.data(), ba.size());

        qDebug() << "pendingDatagramSize: " << this->pendingDatagramSize() << "; "
                 << "ba.size(): " << ba.size() << endl;
    }//忽略发射readReady信号前的数据报o
    if (this->rdf->receive->tryAcquire())
    {
        this->rdf->img_queue->enqueue(QImage::fromData(ba, "PNG"));
        this->rdf->display->release();
    }
}


void UdpSocket::socket_error(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ConnectionRefusedError"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("RemoteHostClosedError"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("HostNotFoundError"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SocketAccessError"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SocketResourceError"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SocketTimeoutError"));
        break;
    case QAbstractSocket::DatagramTooLargeError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("DatagramTooLargeError"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("NetworkError"));
        break;
    case QAbstractSocket::AddressInUseError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("AddressInUseError"));
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SocketAddressNotAvailableError"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("UnsupportedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ProxyAuthenticationRequiredError"));
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SslHandshakeFailedError"));
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("UnfinishedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ProxyConnectionRefusedError"));
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ProxyConnectionClosedError"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ProxyConnectionTimeoutError"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ProxyNotFoundError"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("ProxyProtocolError"));
        break;
    /*
    case QAbstractSocket::OperationError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("OperationError"));
        break;
    case QAbstractSocket::SslInternalError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SslInternalError"));
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("SslInvalidUserDataError"));
        break;
    case QAbstractSocket::TemporaryError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("TemporaryError"));
        break;
    */
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::information(this->label, QObject::tr("UdpSocketError"), QObject::tr("UnknownSocketError"));
        break;
    default:
        break;
    }
}

void UdpSocket::socket_state(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            this->label->setText(QObject::tr("UdpSocketState: Unconnected"));
            break;
        case QAbstractSocket::HostLookupState:
            this->label->setText(QObject::tr("UdpSocketState: HostLookUP"));
            break;
        case QAbstractSocket::ConnectingState:
            this->label->setText(QObject::tr("UdpSocketState: Connecting"));
            break;
        case QAbstractSocket::ConnectedState:
            this->label->setText(QObject::tr("UdpSocketState: Connected"));
            break;
        case QAbstractSocket::BoundState:
            this->label->setText(QObject::tr("SocketStatus: Bound"));
            break;
        case QAbstractSocket::ClosingState:
            this->label->setText(QObject::tr("SocketStatus: Closing"));
            break;
        case QAbstractSocket::ListeningState:
            this->label->setText(QObject::tr("SocketStatus:: Listening"));
            break;

    }
}

DisplayThread::DisplayThread(QObject *parent, ReceiveDisplayFrame *rdf, QLabel *label):
    QThread(parent)
{
    this->rdf = rdf;
    this->label = label;
}

void DisplayThread::run()
{
    while (true)
    {
        if (this->rdf->display->tryAcquire())
        {
            this->image = this->rdf->img_queue->dequeue();
            this->rdf->receive->release();
        }
        this->label->setPixmap(QPixmap::fromImage(this->image));
    }
}
