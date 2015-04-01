#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->csf = new CaptureSendFrame();
    this->cap_thr = new CaptureThread(this->csf);
    this->send_thr = new SendThread(this->csf, this->cap_thr);
    this->tfc = new TransferCmd();

    connect(this->send_thr, SIGNAL(connected()), this->send_thr, SLOT(start()));
    connect(this->send_thr, SIGNAL(disconnected()), this->send_thr, SLOT(quit()));
    connect(this->send_thr, SIGNAL(disconnected()), this->cap_thr, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
