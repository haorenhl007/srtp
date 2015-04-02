#ifndef TRANSFERCMD_H
#define TRANSFERCMD_H

#include "transfercmd_global.h"
#include <QTcpSocket>
#include <QLabel>

class TRANSFERCMDSHARED_EXPORT TransferCmd: public QTcpSocket
{
    Q_OBJECT

public:
    TransferCmd(QObject *parent=0, QLabel *label = nullptr);

private slots:
    void read_cmd();
    void socket_error(QAbstractSocket::SocketError socketError);
    void socket_state(QAbstractSocket::SocketState socketState);

private:
    QLabel *label;
};

#endif // TRANSFERCMD_H
