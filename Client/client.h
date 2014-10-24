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
#include <QList>

class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);
    ~Client();

private slots:
    void enableConnectBtn();
    void setBtnStatus(quint16 enableStatus, quint16 defaultStatus);

    void connectServer();
    void openMatLab();
    void closeMatLab();
    void disconnectServer();
    void openSystem();
    void connectSystem();
    void disconnectSystem();
    void startSystem();
    void stopSystme();
    void closeSystem();
    void displayError(QAbstractSocket::SocketError socketError);
    void displayState(QAbstractSocket::SocketState socketState);
    void readServer();

private:
    QLabel *ipLabel;
    QLineEdit *ipLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QList<QPushButton*> btnList;
    QPushButton *connectBtn;
    QPushButton *openBtn;
    QPushButton *closeBtn;
    QPushButton *disconnectBtn;
    QPushButton *openSystemBtn;
    QPushButton *connectSystemBtn;
    QPushButton *disconnectSystemBtn;
    QPushButton *startSystemBtn;
    QPushButton *stopSystemBtn;
    QPushButton *closeSystemBtn;
    QLabel *statusLabel;
    QHBoxLayout *topLayout;
    QHBoxLayout *mediumLayout;
    QHBoxLayout *bottomLayout;
    QVBoxLayout *mainLayout;

    QTcpSocket *tcpSocket;
};

#endif // CLIENT_H
