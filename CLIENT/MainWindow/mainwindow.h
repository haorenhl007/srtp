#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <receivedisplayframe.h>
#include <transfercmd.h>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QList>

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

private:
    //void openMatLab();
    //void closeMatLab();
private:
    Ui::MainWindow *ui;
    QList<QPushButton*> btnList;

    ReceiveDisplayFrame *rdf;
    TcpSocket *tcp_socket;
    DisplayThread *dis_thr;

    TransferCmd *tfc;
};

#endif // MAINWINDOW_H
