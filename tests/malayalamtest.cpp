#include "malayalamtest.h"

#include <QtTest/QtTest>
#include <QString>

void MalayalamTest::matchChar()
{
    // Initial string that we want to separate into chars
    // You need to have Malayalam fonts installed
    QString string = QString::fromUtf8("യേ");

    QString match2(QString::fromUtf8("യ"));
    QString match3(QString::fromUtf8("േ"));
    //get first char and compare
    QCOMPARE(QString::fromUtf8("യ"), string.left(1));
    //get second char and compare    
    QCOMPARE(QString::fromUtf8("േ"), string.right(1));

}

QTEST_KDEMAIN_CORE( MalayalamTest )

#include "malayalamtest.moc"