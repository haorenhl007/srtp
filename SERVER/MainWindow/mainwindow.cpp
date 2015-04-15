#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <config.h>
#include <QHostAddress>
#include <QHostInfo>
#include <QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->transfer_cmd = new TransferCmd::TransferCmd(this);
    this->transfer_frame = new TransferFrame::TransferFrame(this);

    //在窗体上现实服务端的IP地址列表
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


}

MainWindow::~MainWindow()
{
    delete ui;
}
