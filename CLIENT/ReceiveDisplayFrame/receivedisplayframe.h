#ifndef RECEIVEDISPLAYFRAME_H
#define RECEIVEDISPLAYFRAME_H

#include "receivedisplayframe_global.h"
#include <QQueue>
#include <QThread>
#include <QImage>
#include <QSemaphore>
#include <QUdpSocket>
#include <QLabel>

class RECEIVEDISPLAYFRAMESHARED_EXPORT ReceiveDisplayFrame: public QObject
{
    Q_OBJECT

    friend class DisplayThread;
    friend class UdpSocket;
public:
    ReceiveDisplayFrame(QObject *parent=0, int buffersize=100);

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



class RECEIVEDISPLAYFRAMESHARED_EXPORT UdpSocket: public QUdpSocket
{
    Q_OBJECT
public:
    UdpSocket(QObject *parent=0, ReceiveDisplayFrame *rdf = nullptr, QLabel *label = nullptr);

private slots:
    void receive_frame();
    void socket_error(QAbstractSocket::SocketError socketError);
    void socket_state(QAbstractSocket::SocketState socketState);

private:
    ReceiveDisplayFrame *rdf;
    QLabel *label;

};

#endif // RECEIVEDISPLAYFRAME_H
