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

    connect(this, SIGNAL(connected()), this, SLOT(receive_frame()));
    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
}


void TcpSocket::receive_frame()
{
    //QByteArray ba;
    qDebug() << "call receive frame" << endl;
    QDataStream dt(this);
    QImage img;
    while (true)
    {
        dt >> img;
        if (this->rdf->receive->tryAcquire())
        {
            //this->rdf->img_queue->enqueue(QImage::fromData(ba, "PNG"));
            this->rdf->img_queue->enqueue(img);
            this->rdf->display->release();
        }
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
    qDebug() << "call display thread" << endl;
    while (true)
    {
        if (this->rdf->display->tryAcquire())
        {
            this->image = this->rdf->img_queue->dequeue();
            this->rdf->receive->release();
        }
        this->label->setPixmap(QPixmap::fromImage(this->image));
    }
}
