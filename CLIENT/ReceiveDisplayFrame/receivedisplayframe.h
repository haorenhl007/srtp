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

    friend class ReceiveThread;
    friend class DisplayThread;
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
    DisplayThread(ReceiveDisplayFrame *rdf = nullptr, QLabel *label = nullptr);

protected:
    void run();

private:
    ReceiveDisplayFrame *rdf;

    QImage image;
    QLabel *label;

};



class RECEIVEDISPLAYFRAMESHARED_EXPORT ReceiveThread: public QThread
{
    Q_OBJECT
public:
    ReceiveThread(ReceiveDisplayFrame *rdf = nullptr, DisplayThread *dis_thr=nullptr, QLabel *label = nullptr);
    QUdpSocket *udp_socket;

protected:
    void run();

private slots:
    void socket_error(QAbstractSocket::SocketError socketError);
    void socket_state(QAbstractSocket::SocketState socketState);

private:
    void start();

    ReceiveDisplayFrame *rdf;
    DisplayThread *dis_thr;
    QLabel *label;

};

#endif // RECEIVEDISPLAYFRAME_H
