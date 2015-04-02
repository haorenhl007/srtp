#include "mainwindow.h"
#include <config.h>
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QHostInfo>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->csf = new CaptureSendFrame();
    this->cap_thr = new CaptureThread(this->csf);
    this->send_thr = new SendThread(this->csf, this->cap_thr);
    this->tfc = new TransferCmd();

    QList<QHostAddress> list(IPs());
    QList<QHostAddress>::const_iterator iter = list.begin();
    QString str("Status:\n\n\tIP: ");
    while (iter != list.end())
    {
        str += (*iter).toString();
        str += QString("\n\t");
        iter++;
    }
    this->ui->label->setText(str);


    connect(this->send_thr->udp_socket, SIGNAL(connected()), this->send_thr, SLOT(start()));
    connect(this->send_thr->udp_socket, SIGNAL(disconnected()), this->send_thr, SLOT(quit()));
    connect(this->send_thr->udp_socket, SIGNAL(disconnected()), this->cap_thr, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
