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
    QTcpSocket(parent), in(this), size(0)
{
    this->in.setVersion(QDataStream::Qt_5_3);
    this->rdf = rdf;

    connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    connect(this, SIGNAL(readyRead()), this, SLOT(receive_frame()));
}


void TcpSocket::receive_frame()
{
    if (this->size == 0)
    {
        qDebug() << "this->bytesAbailable(): " << this->bytesAvailable();
        if (this->bytesAvailable() < sizeof(qint64))
            return;
        in >> this->size;
        qDebug() << "this->size" << this->size << " this->bytesAvailable(): " << this->bytesAvailable();
    }

    if (this->bytesAvailable() < this->size)
        return;

    qDebug() << "this->bytesAbailable(): " << this->bytesAvailable();
    QByteArray block = this->read(this->size);
    qDebug() << "block.size()" << block.size();

    if (this->rdf->receive->tryAcquire())
    {
        this->rdf->img_queue->enqueue(QImage::fromData(block, "JPEG"));
        this->rdf->display->release();
    }
    this->size = 0;
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
