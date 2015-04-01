#include "capturesendframe.h"
#include <config.h>
#include <QImage>
#include <QByteArray>
#include <QBuffer>

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


SendThread::SendThread(CaptureSendFrame *csf, CaptureThread *cap_thr)
{
    this->csf = csf;
    this->cap_thr = cap_thr;
    this->udp_socket = new QUdpSocket;
    QHostAddress ip = IPs().first();
    if (!ip.isNull())
    {
        this->udp_socket->bind(ip, udp_port);
    }
}


void SendThread::run()
{
    //namedWindow("test", WINDOW_AUTOSIZE);
    Mat m;
    QByteArray ba;
    QBuffer buffer(&ba);
    while (true)
    {
        this->csf->send->acquire();
        if (this->csf->mat_queue->isEmpty())
            continue;
        m = this->csf->mat_queue->dequeue();
        QImage img= QImage((uchar*) m.data, m.cols, m.rows, m.step, QImage::Format_RGB888);
        img.save(&buffer, "PNG");
        this->udp_socket->write(ba);
        //imshow("test", this->csf->mat_queue->dequeue());
        this->csf->capture->release();
        waitKey(30);
    }
}

void SendThread::start()
{
    this->start();
    this->cap_thr->start();
}
