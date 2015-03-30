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

class ReceiveThread: public QThread, public QUdpSocket
{
    Q_OBJECT
public:
    ReceiveThread(ReceiveDisplayFrame *rdf = nullptr, QLabel *label = nullptr);

protected:
    void run();

private slots:
    void socket_error(QAbstractSocket::SocketError socketError);
    void socket_state(QAbstractSocket::SocketState socketState);

private:
    ReceiveDisplayFrame *rdf;
    QLabel *label;

};

class DisplayThread: public QThread
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

class RDF: public QObject//把上面三个类打包到一起. 作为与MainWindow交换信息的接口
{
    Q_OBJECT

public:
    RDF(QLabel *label = nullptr);

private slots:
    void start_threads();


private:
    ReceiveDisplayFrame *rdf;
    ReceiveThread *rec_thr;
    DisplayThread *dis_thr;

};


#endif // RECEIVEDISPLAYFRAME_H
