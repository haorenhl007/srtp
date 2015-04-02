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

void TcpServer::incomingConnection(int socketId)
{
    qDebug() << "new connection" << endl;

    TcpSocket *tcp_socket = new TcpSocket(this);
    tcp_socket->setSocketDescriptor(socketId);

    CaptureSendFrame *csf = new CaptureSendFrame(this);
    CaptureThread *cap_thr = new CaptureThread(this, csf);
    cap_thr->start();
    UdpSocket *udp_socket = new UdpSocket(this, csf);
    udp_socket->setSocketDescriptor(socketId);
}

TcpSocket::TcpSocket(QObject *parent):
    QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
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
        qDebug() << "camera didn't opened" << endl;
}


UdpSocket::UdpSocket(QObject *parent, CaptureSendFrame *csf):
    QUdpSocket(parent)
{
    this->csf = csf;
    connect(this, SIGNAL(readyRead()), this, SLOT(send_frame()));
}

void UdpSocket::send_frame()
{
    QByteArray ba;
    QBuffer buffer(&ba);
    this->csf->send->acquire();
    if (!this->csf->mat_queue->isEmpty())
    {
        Mat m = this->csf->mat_queue->dequeue();
        QImage img= QImage((uchar*) m.data, m.cols, m.rows, m.step, QImage::Format_RGB888);
        img.save(&buffer, "PNG");
        this->write(buffer.data(), buffer.size());
        //imshow("test", this->csf->mat_queue->dequeue());
        this->csf->capture->release();
        //waitKey(30);
    }
}
