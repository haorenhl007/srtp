#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../config.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket;
    udpSocket = new QUdpSocket;
    btnList.append(ui->connectBtn);
    btnList.append(ui->disconnectBtn);
    btnList.append(ui->openSystemBtn);
    btnList.append(ui->startSystemBtn);
    btnList.append(ui->connectSystemBtn);
    btnList.append(ui->stopSystemBtn);
    btnList.append(ui->disconnectSystemBtn);
    btnList.append(ui->closeSystemBtn);
    connect(ui->ipLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(ui->portLineEdit, SIGNAL(textChanged(QString)), this, SLOT(enableConnectBtn()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    connect(tcpSocket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(displayState(QAbstractSocket::SocketState)));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(readServer()));

    //ui->frameLabel->setPixmap(QPixmap::fromImage(QImage("C:/Users/Administrator/Desktop/SRTP_OPENCV/test.jpg")));
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

    tcpSocket->connectToHost(ui->ipLineEdit->text(), ui->portLineEdit->text().toInt());
}

void MainWindow::on_disconnectBtn_clicked()
{
   tcpSocket->close();
}

void MainWindow::on_openSystemBtn_clicked()
{

    if (tcpSocket->putChar(openCommand) == false)
    {

        QMessageBox::information(this, tr("Write Error"), tr("Error"));
    }
    else
    {
        ui->statusLabel->setText(tr("MatLab is starting"));
    }
    if (tcpSocket->putChar(openSystemCommand) == false)
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
    if (tcpSocket->putChar(connectSystemCommand) == false)
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
    if (tcpSocket->putChar(startSystemCommand) == false)
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
    if (tcpSocket->putChar(closeSystemCommand) == false)
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
    if (tcpSocket->putChar(disconnectSystemCommand) == false)
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

    if (tcpSocket->putChar(closeSystemCommand) == false)
    {
        QMessageBox::information(this, tr("write error"), tr("error"));
    }
    else
    {
        ui->statusLabel->setText(tr("system is closing"));
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("socketError"), tr("ConnectionRefusedError"));
        break;
    case QAbstractSocket::RemoteHostClosedError:
        QMessageBox::information(this, tr("socketError"), tr("RemoteHostClosedError"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("socketError"), tr("HostNotFoundError"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::information(this, tr("socketError"), tr("SocketAccessError"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::information(this, tr("socketError"), tr("SocketResourceError"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::information(this, tr("socketError"), tr("SocketTimeoutError"));
        break;
    case QAbstractSocket::DatagramTooLargeError:
        QMessageBox::information(this, tr("socketError"), tr("DatagramTooLargeError"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::information(this, tr("socketError"), tr("NetworkError"));
        break;
    case QAbstractSocket::AddressInUseError:
        QMessageBox::information(this, tr("socketError"), tr("AddressInUseError"));
        break;
    case QAbstractSocket::SocketAddressNotAvailableError:
        QMessageBox::information(this, tr("socketError"), tr("SocketAddressNotAvailableError"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::information(this, tr("socketError"), tr("UnsupportedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyAuthenticationRequiredError"));
        break;
    case QAbstractSocket::SslHandshakeFailedError:
        QMessageBox::information(this, tr("socketError"), tr("SslHandshakeFailedError"));
        break;
    case QAbstractSocket::UnfinishedSocketOperationError:
        QMessageBox::information(this, tr("socketError"), tr("UnfinishedSocketOperationError"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyConnectionRefusedError"));
        break;
    case QAbstractSocket::ProxyConnectionClosedError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyConnectionClosedError"));
        break;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyConnectionTimeoutError"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyNotFoundError"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::information(this, tr("socketError"), tr("ProxyProtocolError"));
        break;
    /*
    case QAbstractSocket::OperationError:
        QMessageBox::information(this, tr("socketError"), tr("OperationError"));
        break;
    case QAbstractSocket::SslInternalError:
        QMessageBox::information(this, tr("socketError"), tr("SslInternalError"));
        break;
    case QAbstractSocket::SslInvalidUserDataError:
        QMessageBox::information(this, tr("socketError"), tr("SslInvalidUserDataError"));
        break;
    case QAbstractSocket::TemporaryError:
        QMessageBox::information(this, tr("socketError"), tr("TemporaryError"));
        break;
    */
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::information(this, tr("socketError"), tr("UnknownSocketError"));
        break;
    default:
        break;
    }
}

void MainWindow::displayState(QAbstractSocket::SocketState socketState)
{
    switch (socketState)
    {
        case QAbstractSocket::UnconnectedState:
            ui->statusLabel->setText(tr("SocketState: Unconnected"));
            break;
        case QAbstractSocket::HostLookupState:
            ui->statusLabel->setText(tr("SocketState: HostLookUP"));
            break;
        case QAbstractSocket::ConnectingState:
            ui->statusLabel->setText(tr("SocketState: Connecting"));
            break;
        case QAbstractSocket::ConnectedState:
            ui->statusLabel->setText(tr("SocketState: Connected"));
            break;
        case QAbstractSocket::BoundState:
            ui->statusLabel->setText(tr("SocketStatus: Bound"));
            break;
        case QAbstractSocket::ClosingState:
            ui->statusLabel->setText(tr("SocketStatus: Closing"));
            break;
        case QAbstractSocket::ListeningState:
            ui->statusLabel->setText(tr("SocketStatus:: Listening"));
            break;

    }
}


void MainWindow::readServer()
{
    char *c = new char;
    if (tcpSocket->getChar(c) == true)
    {
        switch (*c)
        {
        case openCommand:
            ui->statusLabel->setText(tr("MatLab has been opened:)"));
            break;
        case closeCommand:
            ui->statusLabel->setText(tr("MatLab has been closed:)"));
            break;
        case openSystemCommand:
            ui->statusLabel->setText(tr("System has been opened"));
            break;
        case connectSystemCommand:
            ui->statusLabel->setText(tr("System has been connected"));
            break;
        case disconnectSystemCommand:
            ui->statusLabel->setText(tr("System has been disconnected"));
            break;
        case startSystemCommand:
            ui->statusLabel->setText(tr("System has been started"));
            break;
        case stopSystemCommand:
            ui->statusLabel->setText(tr("System has been stopped"));
            break;
        case closeSystemCommand:
            ui->statusLabel->setText(tr("System has been closed"));
            break;
        default:
            break;
        }
    }
}


ReceiveDisplayFrame::ReceiveDisplayFrame(QObject *parent, int buffersize)
{
    this->img_queue = new QQueue<QImage>();
    this->receive = new QSemaphore(buffersize);
    this->display = new QSemaphore(0);

}

ReceiveThread::ReceiveThread(ReceiveDisplayFrame *rdf)
{
    this->rdf = rdf;
}

void ReceiveThread::run()
{

}



DisplayThread::DisplayThread(ReceiveDisplayFrame *rdf)
{
    this->rdf = rdf;
}

void DisplayThread::run()
{

}
