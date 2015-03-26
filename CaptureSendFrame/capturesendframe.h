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

class CAPTURESENDFRAMESHARED_EXPORT CaptureSendFrame
{
    friend class CaptureThread;
    friend class SendThread;
public:
    CaptureSendFrame(int buffersize=20);

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

class SendThread: public QThread, public QUdpSocket
{
public:
    SendThread(CaptureSendFrame* csf=nullptr);

protected:
    void run();

private:
    CaptureSendFrame *csf;
};

#endif // CAPTURESENDFRAME_H
