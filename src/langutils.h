/*
   Copyright (C) 2007      Pino Toscano <pino@kde.org>
                                        Anne-Marie Mahfouf <annma@kde.org>     
    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

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

#include <QString>
#include <QStringList>

class LangUtils
{
public:
    static bool hasSpecialChars(const QString& lang);
    QStringList getLanguages();

    //QStringList m_languages;
};

#endif
