/*
    SPDX-FileCopyrightText: 2009 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#include "malayalamtest.h"

#include <QTest>
#include <QString>

void MalayalamTest::matchChar()
{
    // Initial string that we want to separate into chars
    // You need to have Malayalam fonts installed
    QString string = QStringLiteral("യേ");

    //get first char and compare
    QCOMPARE(QString::fromUtf8("യ"), string.left(1));
    //get second char and compare    
    QCOMPARE(QString::fromUtf8("േ"), string.right(1));

}

void MalayalamTest::decomposeConsonant()
{
    // Initial consonant that we want to separate into letters
    QString string = QStringLiteral("ഘൊ");

    QCOMPARE(string.length(), 3);
    //first letter
    QCOMPARE(QString::fromUtf8("ഘ"), string.mid(0,1));
    //second letter    
    QCOMPARE(QString::fromUtf8("െ"), string.mid(1,1));
    //third letter    
    QCOMPARE(QString::fromUtf8("ാ"), string.mid(2,1));
    
}

QTEST_MAIN(MalayalamTest)

#include "moc_malayalamtest.cpp"
