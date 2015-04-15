#include "transfercmd.h"
#include <config.h>

namespace TransferCmd {
    TransferCmd::TransferCmd(QObject *parent):
        QTcpServer(parent)
    {
        QHostAddress ip = IPs().first();//使用发现的主机IP的第一个IP
        if (!ip.isNull())
        {
            this->listen(ip, transfer_cmd_port);
        }
    }

    void TransferCmd::incomingConnection(qintptr socketDescriptor)
    {
        TcpSocket *tcp_socket = new TcpSocket(this);
        tcp_socket->setSocketDescriptor(socketDescriptor);
    }


    TcpSocket::TcpSocket(QObject *parent):
        QTcpSocket(parent)
    {
        connect(this, SIGNAL(readyRead()), this, SLOT(readClient()));
        connect(this, SIGNAL(disconnected()), this, SLOT(deleteLater()));
    }


    void TcpSocket::readClient()
    {
        char *c = new char;
        if (this->getChar(c) == true)
        {
            qDebug() << *c << endl;
            switch (*c)
            {
            case openCommand:
                openMatLab();
                break;
            case closeCommand:
                closeMatLab();
                break;
            case openSystemCommand:
                openSystem();
                break;
            case openSystemCommand2:
                openSystem2();
                break;
            case connectSystemCommand:
                connectSystem();
                break;
            case disconnectSystemCommand:
                disconnectSystem();
                break;
            case startSystemCommand:
                startSystem();
                break;
            case stopSystemCommand:
                stopSystem();
                break;

            case closeSystemCommand:
                closeSystem();
                break;
            case closeSystemCommand2:
                closeSystem2();
                break;
            default:
                break;
            }
        }
    }

    void TcpSocket::openMatLab()
    {
        if (this->ep = engOpen(""))
        {
            this->putChar(openCommand);
        }

    }

    void TcpSocket::closeMatLab()
    {
        engClose(ep);
        this->putChar(closeCommand);
    }

    void TcpSocket::openSystem()
    {
        engEvalString(ep, CDWORKDIRECTORY);
        engEvalString(ep, OPENSYSTEM);
        this->putChar(openSystemCommand);
    }

    void TcpSocket::openSystem2()
    {
        engEvalString(ep, CDWORKDIRECTORY);
        engEvalString(ep, OPENSYSTEM2);
        this->putChar(openSystemCommand2);
    }

    void TcpSocket::connectSystem()
    {
        engEvalString(ep, CONNECTSYSTEM);
        qDebug() << "exec connecting system";
        this->putChar(connectSystemCommand);
    }

    void TcpSocket::disconnectSystem()
    {
        engEvalString(ep, DISCONNECTSYSTEM);
        this->putChar(disconnectSystemCommand);
    }

    void TcpSocket::startSystem()
    {
        engEvalString(ep, STARTSYSTEM);
        this->putChar(startSystemCommand);
    }
    void TcpSocket::stopSystem()
    {
        engEvalString(ep, STOPSYSTEM);
        this->putChar(stopSystemCommand);
    }

    void TcpSocket::closeSystem()
    {
        engEvalString(ep, CLOSESYSTEM);
        this->putChar(closeSystemCommand);
    }

    void TcpSocket::closeSystem2()
    {
        engEvalString(ep, CLOSESYSTEM2);
        this->putChar(closeSystemCommand2);
    }
}
