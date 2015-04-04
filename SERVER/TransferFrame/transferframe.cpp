#include "transferframe.h"
#include <config.h>
#include <QImage>
#include <QBuffer>


namespace TransferFrame {
    TransferFrame::TransferFrame(QObject *parent):
        QTcpServer(parent)
    {
        QHostAddress ip = IPs().first();
        if (!ip.isNull())
        {
            this->listen(ip, transfer_frame_port);
        }
    }

    void TransferFrame::incomingConnection(qintptr socketDescriptor)
    {
        CaptureSendFrame *csf = new CaptureSendFrame(this);

        CaptureThread *cap_thr = new CaptureThread(this, csf);
        cap_thr->start();

        TcpSocket *tcp_socket = new TcpSocket(this, csf);
        tcp_socket->setSocketDescriptor(socketDescriptor);
        tcp_socket->send_frame();

        connect(tcp_socket, SIGNAL(disconnected()), cap_thr, SLOT(deleteLater()));
        connect(tcp_socket, SIGNAL(disconnected()), tcp_socket, SLOT(deleteLater()));
        connect(tcp_socket, SIGNAL(disconnected()), csf, SLOT(deleteLater()));
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


    TcpSocket::TcpSocket(QObject *parent, CaptureSendFrame *csf):
        QTcpSocket(parent)
    {
        this->csf = csf;
    }



    void TcpSocket::send_frame()
    {
        namedWindow("test", WINDOW_AUTOSIZE);
        qint64 write_size;
        Mat m;
        QImage img;
        while (true)
        {
            QBuffer buffer;
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out.setVersion(QDataStream::Qt_5_3);
            this->csf->send->acquire();
            if (!this->csf->mat_queue->isEmpty())
            {
                m = this->csf->mat_queue->dequeue();
                img= QImage((uchar*) m.data, m.cols, m.rows, m.step, QImage::Format_RGB888);
                img.save(&buffer, "JPEG");
                out << qint64(buffer.size());
                block.append(buffer.data());
                write_size = this->write(block);

                imshow("test", m);
                waitKey(30);

                qDebug() << "mat_queue->size()" << this->csf->mat_queue->size()
                         << "; " << "buffer.size: " << buffer.size()
                         << "; " << "sizeof(qint32(buffer.size()))" << sizeof(qint64(buffer.size()))
                         << "; " << "send size: " << write_size;
            }
            this->csf->capture->release();
        }
    }
}
