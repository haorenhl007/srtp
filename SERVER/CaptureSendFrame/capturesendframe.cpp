#include "capturesendframe.h"
#include <config.h>


CaptureSendFrame::CaptureSendFrame(QObject *parent, int buffersize)
{
    this->mat_queue = new QQueue<Mat>();
    this->capture = new QSemaphore(buffersize);
    this->send = new QSemaphore(0);
}

CaptureThread::CaptureThread(CaptureSendFrame *csf)
{
    this->csf = csf;
}


void CaptureThread::run()
{
    Mat m;
    VideoCapture cap(0);//摄像头的设备号, 根据实际情况修改.$ ls /dev/video*
    //cap.set(CV_CAP_PROP_FRAME_WIDTH, 1024);
    //cap.set(CV_CAP_PROP_FRAME_HEIGHT, 960);
    if (cap.isOpened())
    {
        while(true)
        {
            cap >> m;
            if (this->csf->capture->tryAcquire())
            {
                this->csf->mat_queue->enqueue(m);
                this->csf->send->release();
            }
        }
    }
    else
        printf("not opened\n");
}


SendThread::SendThread(CaptureSendFrame *csf)
{
    this->csf = csf;
    QHostAddress ip = IPs().first();
    if (!ip.isNull())
    {
        this->bind(ip, udp_port);
    }
}


void SendThread::run()
{
    namedWindow("test", WINDOW_AUTOSIZE);
    while (true)
    {
        this->csf->send->acquire();
        if (this->csf->mat_queue->isEmpty())
            continue;
        imshow("test", this->csf->mat_queue->dequeue());
        this->csf->capture->release();
        waitKey(30);
    }
}

