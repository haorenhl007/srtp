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

    friend class DisplayThread;//使用友元类是因为img_queue,receive,display的访问权限都是私有
    friend class TcpSocket;    //但是DisplayThread和TcpSocket类都需要访问它们
public:
    ReceiveDisplayFrame(QObject *parent=0, int buffersize=50);

private:
    QQueue<QImage> *img_queue;
    QSemaphore *receive;
    QSemaphore *display;
};


class RECEIVEDISPLAYFRAMESHARED_EXPORT DisplayThread: public QThread
{
    Q_OBJECT
public:
    //DisplayThread类需要访问ReceiveDisplayFrame类,所以参数中需要有一个执行它的指针rdf,图片需要在label上刷新.
    DisplayThread(QObject *parent=0, ReceiveDisplayFrame *rdf = nullptr, QLabel *label = nullptr);

protected:
    void run();//线程start后执行run

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

class RECEIVEDISPLAYFRAMESHARED_EXPORT TcpSocket: public QTcpSocket
{
    Q_OBJECT
public:
    TcpSocket(QObject *parent=0, ReceiveDisplayFrame *rdf = nullptr);

private slots:
    void receive_frame();

private:
    ReceiveDisplayFrame *rdf;
    QDataStream in;
    qint64 size;
};

#endif // RECEIVEDISPLAYFRAME_H
