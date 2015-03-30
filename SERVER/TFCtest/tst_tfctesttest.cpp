#include <QString>
#include <QtTest>

#include <transfercmd.h>
#include <iostream>

using namespace std;

class TFCtestTest : public QObject
{
    Q_OBJECT

public:
    TFCtestTest();

private Q_SLOTS:
    void testCase1();
};

TFCtestTest::TFCtestTest()
{

    TransferCmd t;
    char c;
    cin >> c;
}

void TFCtestTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TFCtestTest)

#include "tst_tfctesttest.moc"
