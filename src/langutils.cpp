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

//project headers
#include "langutils.h"
#include "prefs.h"

#include <QDir>

#include <kdebug.h>
#include <kglobal.h>
#include <kstandarddirs.h>

bool LangUtils::hasSpecialChars(const QString& lang)
{
    if (lang== "cs"
        || lang== "da"
        || lang== "sk"
        || lang== "es"
        || lang== "de"
        || lang== "nds")
        return true;
    return false;
}

QStringList LangUtils::getLanguages()
{
    QStringList m_languages;
    m_languages.clear();
    //the program scans in klettres/data/ to see what languages data is found
    QStringList mdirs = KGlobal::dirs()->findDirs("data", "klettres/");
    //if (mdirs.isEmpty()) return NULL;
    for (QStringList::Iterator it =mdirs.begin(); it !=mdirs.end(); ++it ) {
        QDir dir(*it);
        m_languages += dir.entryList(QDir::Dirs, QDir::Name);
        m_languages.removeAll(".");
        m_languages.removeAll("..");
    }
    m_languages.removeAll("pics");
    m_languages.removeAll("data");
    m_languages.removeAll("icons");
    m_languages.sort();
    //if (m_languages.isEmpty()) return;
    Prefs::setLanguages(m_languages);
    Prefs::writeConfig();
    //find duplicated entries in KDEDIR and KDEHOME
    QStringList temp_languages;
    for (int i=0;  i<m_languages.count(); i++)
    {
        if (m_languages.count(m_languages[i])>1) {
            temp_languages.append(m_languages[i]);
            m_languages.removeAll(m_languages[i]);
        }
    for (int i=0;  i<temp_languages.count(); i++)
    {
        if (i%2==0)
        m_languages.append(temp_languages[i]);//append 1 of the 2 instances found
    }
    temp_languages.clear();
    }
//TODO TEST in FRENCH
    m_languages.sort();
    //write the present languages in config so they cannot be downloaded
    KConfigGroup config(KGlobal::config(), "KNewStuffStatus");
    for (int i=0;  i<m_languages.count(); i++)
    {
        QString tmp = m_languages[i];
        if (!config.readEntry(tmp, QString()).isEmpty())
            config.writeEntry(tmp, QDate::currentDate().toString());
    }
    kDebug() <<m_languages << endl;
    return m_languages;
}


