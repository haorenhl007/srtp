#ifndef TRANSFERCMD_H
#define TRANSFERCMD_H

#include "transfercmd_global.h"
#include <QTcpServer>
#include <QTcpSocket>

namespace TransferCmd {
    class TRANSFERCMDSHARED_EXPORT TransferCmd: public QTcpServer
    {
        Q_OBJECT

    public:
        TransferCmd(QObject *parent=0);

    private:
        void incomingConnection(qintptr socketDescriptor);

    };


    class TcpSocket: public QTcpSocket
    {
        Q_OBJECT
    public:
        explicit TcpSocket(QObject *parent = 0);

    private slots:
        void readClient();

    private:
        void openMatLab();
        void closeMatLab();
        void openSystem();
        void connectSystem();
        void disconnectSystem();
        void startSystem();
        void stopSystem();
        void closeSystem();

    private:
        //Engine *ep;
    };
    }

#endif // TRANSFERCMD_H
