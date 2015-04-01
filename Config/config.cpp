#include "config.h"

QList<QHostAddress> IPs()
{
    QList<QHostAddress> r;
    QList<QHostAddress> addres(QNetworkInterface::allAddresses());
    QList<QHostAddress>::const_iterator addre = addres.begin();
    while (addre != addres.end())
    {
        if ((*addre).protocol() == QAbstractSocket::IPv4Protocol && (*addre) != QHostAddress::LocalHost)
            r.append(*addre);
        addre++;
    }
    return r;
}

Config::Config()
{
}
