#include <QString>
#include <QtTest>

#include <controlprotocol.h>
#include <iostream>

using namespace std;

class CPtestTest : public QObject
{
    Q_OBJECT

public:
    CPtestTest();

private Q_SLOTS:
    void testCase1();
};

CPtestTest::CPtestTest()
{
    ControlProtocol cp;
    QList<QHostAddress> ips(cp.IPs());
    QList<QHostAddress>::const_iterator citer;
    for (citer = ips.begin(); citer != ips.end(); citer++)
    {
        qDebug() << (*citer).toString() << endl;
    }

}

void CPtestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(CPtestTest)

#include "tst_cptesttest.moc"
