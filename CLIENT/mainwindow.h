#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QString>
#include <QList>
#include <QThread>
#include <QQueue>
#include <QSemaphore>
#include <QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_connectBtn_clicked();

    void on_disconnectBtn_clicked();

    void on_openSystemBtn_clicked();

    void on_connectSystemBtn_clicked();

    void on_startSystemBtn_clicked();

    void on_stopSystemBtn_clicked();

    void on_disconnectSystemBtn_clicked();

    void on_closeSystemBtn_clicked();

    void enableConnectBtn();

    void setBtnStatus(quint16 enableStatus, quint16 defaultStatus);

    void displayError(QAbstractSocket::SocketError socketError);

    void displayState(QAbstractSocket::SocketState socketState);

    void readServer();

private:
    //void openMatLab();
    //void closeMatLab();
private:
    Ui::MainWindow *ui;
    QList<QPushButton*> btnList;
    QTcpSocket *tcpSocket;
    QUdpSocket *udpSocket;
};

class ReceiveDisplayFrame: public QObject
{
    Q_OBJECT

    friend class ReceiveThread;
    friend class DisplayThread;
public:
    ReceiveDisplayFrame(QObject *parent=0, int buffersize=100);

private:
    QQueue<QImage> *img_queue;
    QSemaphore *receive;
    QSemaphore *display;
};

class ReceiveThread: public QThread, public QUdpSocket
{
public:
    ReceiveThread(ReceiveDisplayFrame *rdf = nullptr);

protected:
    void run();

private:
    ReceiveDisplayFrame *rdf;

};

class DisplayThread: public QThread
{
public:
    DisplayThread(ReceiveDisplayFrame *rdf = nullptr);

protected:
    void run();

private:
    ReceiveDisplayFrame *rdf;

};

#endif // MAINWINDOW_H
