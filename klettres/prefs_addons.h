/***************************************************************************
 *   Copyright (C) 2004 by Waldo Bastian                             *
 *   bastian@kde.org                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
 public:
static QString defaultLanguage();
static void setLanguages(const QStringList &languages)
{
    Prefs::self()->m_languages = languages;
}

static void setLanguageNumber(int i)
{
    setLanguage(Prefs::self()->m_languages[i]);
}
static int languageNumber()
{
    int i = Prefs::self()->m_languages.findIndex(language());
    if (i != -1)
        return i;
    i = Prefs::self()->m_languages.findIndex(defaultLanguage());
    if (i != -1)
        return i;
    i = Prefs::self()->m_languages.findIndex("en");
    if (i != -1)
        return i;

    return 0;
}
QStringList m_languages;
