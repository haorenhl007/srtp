#ifndef TRANSFERFRAME_H
#define TRANSFERFRAME_H

#include "transferframe_global.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QQueue>
#include <QSemaphore>

#ifdef _WIN32
    #include <opencv2/opencv.hpp>
#else
    #include <opencv2/opencv.hpp>
    #include <opencv2/highgui/highgui.hpp>
#endif
using namespace cv;

namespace TransferFrame {
    class TRANSFERFRAMESHARED_EXPORT TransferFrame: public QTcpServer
    {
        Q_OBJECT

    public:
        TransferFrame(QObject *parent=0);

    private:
        void incomingConnection(qintptr socketDescriptor);
    };


    class CaptureSendFrame: public QObject
    {
        Q_OBJECT

        friend class CaptureThread;
        friend class TcpSocket;
    public:
        CaptureSendFrame(QObject *parent=0, int buffersize=20);

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

    class TcpSocket: public QTcpSocket
    {
        Q_OBJECT
    public:
        TcpSocket(QObject *parent=0, CaptureSendFrame* csf=nullptr);
        void send_frame();

    private:
        CaptureSendFrame *csf;
        CaptureThread *cap_thr;

    };
}

#endif // TRANSFERFRAME_H
