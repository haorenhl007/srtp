#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QString>

class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);
    ~Client();

private slots:
    void enableConnectBtn();
    void connectServer();
    void openMatLab();
    void initMatLab();
    void closeMatLab();
    void disconnectServer();
    void displayError(QAbstractSocket::SocketError socketError);
    void displayState(QAbstractSocket::SocketState socketState);
    void readServer();

private:
    QLabel *ipLabel;
    QLineEdit *ipLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *connectBtn;
    QPushButton *openBtn;
    QPushButton *initBtn;
    QPushButton *closeBtn;
    QPushButton *disconnectBtn;
    QLabel *statusLabel;
    QHBoxLayout *topLayout;
    QHBoxLayout *bottomLayout;
    QVBoxLayout *mainLayout;

    QTcpSocket *tcpSocket;
};

#endif // CLIENT_H
