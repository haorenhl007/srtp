#ifndef CAPTURESENDFRAME_H
#define CAPTURESENDFRAME_H

#include "capturesendframe_global.h"

#include <QThread>
#include <QUdpSocket>
#include <QQueue>
#include <QSemaphore>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class CAPTURESENDFRAMESHARED_EXPORT CaptureSendFrame: public QObject
{
    Q_OBJECT

    friend class CaptureThread;
    friend class SendThread;
public:
    CaptureSendFrame(QObject *parent=0, int buffersize=100);

private:
    QQueue<Mat> *mat_queue;
    QSemaphore *capture;
    QSemaphore *send;

};

class CaptureThread: public QThread
{
public:
    CaptureThread(CaptureSendFrame *csf=nullptr);

protected:
    void run();

private:
    CaptureSendFrame *csf;
};

class SendThread: public QThread
{
public:
    SendThread(CaptureSendFrame* csf=nullptr, CaptureThread *cap_thr=nullptr);
    void start();

public:
    QUdpSocket *udp_socket;

protected:
    void run();

private:
    CaptureSendFrame *csf;
    CaptureThread *cap_thr;
};

#endif // CAPTURESENDFRAME_H
