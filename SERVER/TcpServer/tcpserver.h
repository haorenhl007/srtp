#ifndef TCPSERVER_H
#define TCPSERVER_H

#include "tcpserver_global.h"

#ifdef _WIN32
    #include <opencv2/opencv.hpp>
#else
    #include <opencv2/opencv.hpp>
    #include <opencv2/highgui/highgui.hpp>
#endif
using namespace cv;

#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QThread>
#include <QQueue>
#include <QSemaphore>



class TCPSERVERSHARED_EXPORT TcpServer: QTcpServer
{
    Q_OBJECT
public:
    TcpServer(QObject *parent=0);

protected:
    void incomingConnection(int socketId);

private:

};

class TcpSocket: public QTcpSocket
{
    Q_OBJECT
public:
    explicit TcpSocket(QObject *parent = 0);

private slots:
    void readClient();

private:
    void openMatLab();
    void closeMatLab();
    void openSystem();
    void connectSystem();
    void disconnectSystem();
    void startSystem();
    void stopSystem();
    void closeSystem();

private:
    //Engine *ep;
};


class CaptureSendFrame: public QObject
{
    Q_OBJECT

    friend class CaptureThread;
    friend class UdpSocket;
public:
    CaptureSendFrame(QObject *parent=0, int buffersize=100);

private:
    QQueue<Mat> *mat_queue;
    QSemaphore *capture;
    QSemaphore *send;

};

class CaptureThread: public QThread
{
    Q_OBJECT
public:
    CaptureThread(QObject *parent=0, CaptureSendFrame *csf=nullptr);

protected:
    void run();

private:
    CaptureSendFrame *csf;
};

class UdpSocket: public QUdpSocket
{
    Q_OBJECT
public:
    UdpSocket(QObject *parent=0, CaptureSendFrame* csf=nullptr);

private slots:
    void send_frame();

private:
    CaptureSendFrame *csf;
    CaptureThread *cap_thr;
};

#endif // TCPSERVER_H
