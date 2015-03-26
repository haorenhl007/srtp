#include "capturesendframe.h"


CaptureSendFrame::CaptureSendFrame(int buffersize)
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
    VideoCapture cap(1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
    if (cap.isOpened())
    {
        while(true)
        {
            cap >> m;
            if (this->csf->capture->tryAcquire())
            {
                this->csf->mat_queue->enqueue(m);
                printf("en: %d\n", this->csf->mat_queue->length());
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
        printf("de: %d\n", this->csf->mat_queue->length());
        this->csf->capture->release();
        waitKey(30);
    }
}

