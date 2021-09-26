/*
    SPDX-FileCopyrightText: 2007 Pino Toscano <pino@kde.org>
    SPDX-FileCopyrightText: 2007-2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef LANGUTILS_H
#define LANGUTILS_H


#include <QStringList>

class LangUtils
{
public:
    static bool hasSpecialChars(const QString& lang);
    ///Indian languages cannot have isLetter()
    static bool isIndian(const QString& lang);
    ///Available languages ISO names
    static QStringList getLanguages();
    static void writeLangConfig();
    ///All available languages translated names
    static QStringList getLanguagesNames(const QStringList &languagesList);
};

#endif
