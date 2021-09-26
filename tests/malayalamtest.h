/*
    SPDX-FileCopyrightText: 2009 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef MALAYALAMTEST_H
#define MALAYALAMTEST_H

#include <QObject>

class MalayalamTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void matchChar();
    void decomposeConsonant();

};


#endif /* MALAYALAMTEST_H */
