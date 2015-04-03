#include "tcpserver.h"
#include <config.h>
#include <QImage>
#include <QByteArray>
#include <QBuffer>


TcpServer::TcpServer(QObject *parent):
    QTcpServer(parent)
{
    QHostAddress ip = IPs().first();
    if (!ip.isNull())
    {
        this->listen(ip, tcp_port);
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    TcpSocket *tcp_socket = new TcpSocket(this);
    tcp_socket->setSocketDescriptor(socketDescriptor);


    CaptureSendFrame *csf = new CaptureSendFrame(this);

    CaptureThread *cap_thr = new CaptureThread(this, csf);
    cap_thr->start();

    SendFrame *send_frame = new SendFrame(this, csf);
}

TcpSocket::TcpSocket(QObject *parent):
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}


void TcpSocket::readClient()
{
    char *c = new char;
    if (this->getChar(c) == true)
    {
        switch (*c)
        {
        case openCommand:
            openMatLab();
            break;
        case closeCommand:
            closeMatLab();
            break;
        case openSystemCommand:
            openSystem();
            break;
        case connectSystemCommand:
            connectSystem();
            break;
        case disconnectSystemCommand:
            disconnectSystem();
            break;
        case startSystemCommand:
            startSystem();
            break;
        case stopSystemCommand:
            stopSystem();
            break;
        case closeSystemCommand:
            closeSystem();
            break;
        default:
            break;
        }
    }
}

void TcpSocket::openMatLab()
{
    //if (this->ep = engOpen(""))
    //{
        this->putChar(openCommand);
    //}

}

void TcpSocket::closeMatLab()
{
    //engClose(ep);
    this->putChar(closeCommand);
}

void TcpSocket::openSystem()
{
    //engEvalString(ep, CDWORKDIRECTORY);
    //engEvalString(ep, OPENSYSTEM);
    this->putChar(openSystemCommand);
}

void TcpSocket::connectSystem()
{
    //engEvalString(ep, CONNECTSYSTEM);
    this->putChar(connectSystemCommand);
}

void TcpSocket::disconnectSystem()
{
    //engEvalString(ep, DISCONNECTSYSTEM);
    this->putChar(connectSystemCommand);
}

void TcpSocket::startSystem()
{
    //engEvalString(ep, STARTSYSTEM);
    this->putChar(startSystemCommand);
}
void TcpSocket::stopSystem()
{
    //engEvalString(ep, STOPSYSTEM);
    this->putChar(stopSystemCommand);
}

void TcpSocket::closeSystem()
{
    //engEvalString(ep, CLOSESYSTEM);
    this->putChar(stopSystemCommand);
}


CaptureSendFrame::CaptureSendFrame(QObject *parent, int buffersize):
    QObject(parent)
{
    this->mat_queue = new QQueue<Mat>();
    this->capture = new QSemaphore(buffersize);
    this->send = new QSemaphore(0);
}

CaptureThread::CaptureThread(QObject *parent, CaptureSendFrame *csf):
    QThread(parent)
{
    this->csf = csf;
}

void CaptureThread::run()
{
    Mat m;
    VideoCapture cap(1);//摄像头的设备号, 根据实际情况修改.$ ls /dev/video*
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
        qDebug() << "camera didn't opened" << endl;
}


SendFrame::SendFrame(QObject *parent, CaptureSendFrame *csf):
    QTcpSocket(parent)
{
    this->csf = csf;
    //connect(this, SIGNAL(readyRead()), this, SLOT(process_message());
}



void SendFrame::send_frame()
{
    //namedWindow("test", WINDOW_AUTOSIZE);
    Mat m;
    QImage img;
    QByteArray ba;
    QBuffer buffer(&ba);
    while (true)
    {
        this->csf->send->acquire();
        if (!this->csf->mat_queue->isEmpty())
        {
            m = this->csf->mat_queue->dequeue();
            img= QImage((uchar*) m.data, m.cols, m.rows, m.step, QImage::Format_RGB888);
            img.save(&buffer, "PNG");

            qDebug() << "img.byteCount: " << img.byteCount()
                     << ";\t" << "buffer.size: " << buffer.size() << endl;
            //this->write(buffer.data(), buffer.size());
            imshow("test", m);
            waitKey(10);
        }
        this->csf->capture->release();
    }
}
