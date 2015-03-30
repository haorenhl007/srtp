#ifndef HOSTINFO_H
#define HOSTINFO_H

#include "hostinfo_global.h"
#include <QHostAddress>
#include <QList>

class HOSTINFOSHARED_EXPORT HostInfo
{

public:
    QList<QHostAddress> ip_queue;
    const int tcp_port = 8000;
    const int udp_port = 8080;

private:

};

#endif // HOSTINFO_H
