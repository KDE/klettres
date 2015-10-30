/*
 *  Copyright (C) 2009  Anne-Marie Mahfouf   <annma@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License version 2 as published by the Free Software Foundation;
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
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

