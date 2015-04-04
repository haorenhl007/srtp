#include "receivedisplayframe.h"
#include <config.h>
#include <QMessageBox>

ReceiveDisplayFrame::ReceiveDisplayFrame(QObject *parent, int buffersize):
    QObject(parent)
{
    this->img_queue = new QQueue<QImage>();
    this->receive = new QSemaphore(buffersize);
    this->display = new QSemaphore(0);
}

TcpSocket::TcpSocket(QObject *parent, ReceiveDisplayFrame *rdf):
    QTcpSocket(parent)
{
    this->rdf = rdf;

    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(readyRead()), this, SLOT(receive_frame()));
}


void TcpSocket::receive_frame()
{
    QByteArray ba;
    ba = this->readAll();
    qDebug() << "ba.size: " << ba.size() << endl;
    if (this->rdf->receive->tryAcquire())
    {
        this->rdf->img_queue->enqueue(QImage::fromData(ba, "JPEG"));
        this->rdf->display->release();
    }
}

DisplayThread::DisplayThread(QObject *parent, ReceiveDisplayFrame *rdf, QLabel *label):
    QThread(parent)
{
    this->rdf = rdf;
    this->label = label;
}

void DisplayThread::run()
{
    while (true)
    {
        if (this->rdf->display->tryAcquire())
        {
            this->image = this->rdf->img_queue->dequeue();
            this->label->setPixmap(QPixmap::fromImage(this->image));
            this->rdf->receive->release();
        }
    }
}
