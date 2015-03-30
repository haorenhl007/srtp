#include <QString>
#include <QtTest>
#include <QTest>

#include <capturesendframe.h>
#include <iostream>
using namespace std;

class CSFtestTest : public QObject
{
    Q_OBJECT

public:
    CSFtestTest();

private Q_SLOTS:
    void testCase1();
};

CSFtestTest::CSFtestTest()
{
    CaptureSendFrame *csf = new CaptureSendFrame;
    CaptureThread *capthr = new CaptureThread(csf);
    SendThread *sendthr = new SendThread(csf);
    capthr->start();
    sendthr->start();
    char c;
    cin >> c;
}

void CSFtestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}


QTEST_APPLESS_MAIN(CSFtestTest)

#include "tst_csftesttest.moc"
