#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QTcpSocket>
#include "engine.h"

class ClientSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit ClientSocket(QObject *parent = 0);

signals:

public slots:
    void readClient();

private:
    void openMatLab();
    void closeMatLab();

private:
    Engine *ep;
};

#endif // CLIENTSOCKET_H
