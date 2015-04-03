#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <config.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnList.append(ui->connectBtn);
    btnList.append(ui->disconnectBtn);
    btnList.append(ui->openSystemBtn);
    btnList.append(ui->startSystemBtn);
    btnList.append(ui->connectSystemBtn);
    btnList.append(ui->stopSystemBtn);
    btnList.append(ui->disconnectSystemBtn);
    btnList.append(ui->closeSystemBtn);

    this->rdf = new ReceiveDisplayFrame(this);
    this->dis_thr = new DisplayThread(this, this->rdf, this->ui->statusLabel);
    this->udp_socket = new UdpSocket(this, this->rdf, this->ui->statusLabel);

    this->tfc = new TransferCmd(this, this->ui->statusLabel);

    connect(ui->ipLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(this->udp_socket, SIGNAL(connected()), this->dis_thr, SLOT(start()));
    connect(this->udp_socket, SIGNAL(disconnected()), this->dis_thr, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableConnectBtn()
{
}

void MainWindow::setBtnStatus(quint16 enableStatus, quint16 defaultStatus)
{
    QList<QPushButton*>::const_iterator i = btnList.end() - 1;
    do
    {
        if (enableStatus % 2 == 1)
        {
            (*i)->setEnabled(true);
        }
        else
        {
           (*i)->setEnabled(false);
        }
        if (defaultStatus % 2 == 1)
        {
            (*i)->setDefault(true);
        }
        else
        {
            (*i)->setDefault(false);
        }
        i = i - 1;
    } while ((enableStatus /= 2) > 0 || i >= btnList.begin());
}

void MainWindow::on_connectBtn_clicked()
{

    this->tfc->connectToHost(ui->ipLineEdit->text(), tcp_port);
    this->udp_socket->connectToHost(ui->ipLabel->text(), udp_port);
}

void MainWindow::on_disconnectBtn_clicked()
{
   this->tfc->close();
   this->udp_socket->close();
}

void MainWindow::on_openSystemBtn_clicked()
{

    if (this->tfc->putChar(openCommand) == false)
    {

        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("MatLab is starting"));
    }
    if (this->tfc->putChar(openSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("System is opening"));
    }
}

void MainWindow::on_connectSystemBtn_clicked()
{
    if (this->tfc->putChar(connectSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("Connecting to System"));
    }
}

void MainWindow::on_startSystemBtn_clicked()
{
    if (this->tfc->putChar(startSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("System is strarting"));
    }
}

void MainWindow::on_stopSystemBtn_clicked()
{
    if (this->tfc->putChar(closeSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("System is closing"));
    }
}

void MainWindow::on_disconnectSystemBtn_clicked()
{
    if (this->tfc->putChar(disconnectSystemCommand) == false)
    {
        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("Disconnecting to system"));
    }
}

void MainWindow::on_closeSystemBtn_clicked()
{

    if (this->tfc->putChar(closeSystemCommand) == false)
    {
        QMessageBox::information(this, tr("write error"), tr("error"));
    }
    else
    {
        ui->statusLabel->setText(tr("system is closing"));
    }
}
