/*
    Copyright 2007 Pino Toscano <pino@kde.org>
    Copyright 2007-2008 Anne-Marie Mahfouf <annma@kde.org>     

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
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
