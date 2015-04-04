#ifndef RECEIVEDISPLAYFRAME_H
#define RECEIVEDISPLAYFRAME_H

#include "receivedisplayframe_global.h"
#include <QQueue>
#include <QThread>
#include <QImage>
#include <QSemaphore>
#include <QTcpSocket>
#include <QLabel>

class RECEIVEDISPLAYFRAMESHARED_EXPORT ReceiveDisplayFrame: public QObject
{
    Q_OBJECT

    friend class DisplayThread;
    friend class TcpSocket;
public:
    ReceiveDisplayFrame(QObject *parent=0, int buffersize=20);

private:
    QQueue<QImage> *img_queue;
    QSemaphore *receive;
    QSemaphore *display;
};


class RECEIVEDISPLAYFRAMESHARED_EXPORT DisplayThread: public QThread
{
    Q_OBJECT
public:
    DisplayThread(QObject *parent=0, ReceiveDisplayFrame *rdf = nullptr, QLabel *label = nullptr);

protected:
    void run();

private:
    ReceiveDisplayFrame *rdf;

    QImage image;
    QLabel *label;

};


/*
使用UdpSocket发送有点不妥

Datagrams are always written as one block.
The maximum size of a datagram is highly platform-dependent,
but can be as low as 8192 bytes. If the datagram is too large,
this function will return -1 and error() will return DatagramTooLargeError.

Sending datagrams larger than 512 bytes is in general disadvised,
as even if they are sent successfully, they are likely to be fragmented
by the IP layer before arriving at their final destination.
*/

class RECEIVEDISPLAYFRAMESHARED_EXPORT TcpSocket: public QThread
{
    Q_OBJECT
public:
    TcpSocket(QObject *parent=0, ReceiveDisplayFrame *rdf = nullptr);
    QTcpSocket *tcp_socket;

private slots:
    void test();

private:
    void run();

    ReceiveDisplayFrame *rdf;

};

#endif // RECEIVEDISPLAYFRAME_H
