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

//project headers
#include "langutils.h"
#include "prefs.h"

#include <QDir>

#include <KDebug>
#include <KGlobal>
#include <KLocale>
#include <KStandardDirs>

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
	
	//find duplicated entries in KDEDIR and KDEHOME
	QStringList temp_languages;
	for (int i=0;  i<m_languages.count(); i++)  {
		if (m_languages.count(m_languages[i])>1)  {
			temp_languages.append(m_languages[i]);
			m_languages.removeAll(m_languages[i]);
		}
		for (int i=0;  i<temp_languages.count(); i++)  {
			if (i%2==0)
			m_languages.append(temp_languages[i]);//append 1 of the 2 instances found
		}
		temp_languages.clear();
	}
	//TODO TEST in FRENCH
	m_languages.sort();
	kDebug() <<m_languages;
	return m_languages;
}

QStringList LangUtils::getLanguagesNames(QStringList languagesList)
{
    //we look in $KDEDIR/share/locale/all_languages from /kdelibs/kdecore/all_languages
    //to find the name of the country
    //corresponding to the code and the language the user set
    QStringList languagesNames;
    KConfig entry(KStandardDirs::locate("locale", "all_languages"));

    foreach(QString language, languagesList) {
        if (language == "hi-ro")
            languagesNames.append(i18n("Romanized Hindi"));
        else if (language == "lug_UG")
            languagesNames.append(i18n("Luganda"));
        else
        {
            KConfigGroup group = entry.group(language);
	    QString languageName = group.readEntry("Name");
	    if (languageName.isEmpty()) {
		languageName = i18n("None");
	    }
	    languagesNames.append(languageName);
        }
    }
    //never sort m_languageNames as it's m_languages translated
    return languagesNames;
}

void LangUtils::writeLangConfig()
{
	//write the present languages in config so they cannot be downloaded
	KConfigGroup config(KGlobal::config(), "KNewStuffStatus");
	QStringList m_languages = getLanguages();
	for (int i=0;  i<m_languages.count(); i++)  {
		QString tmp = m_languages[i];
		if (!config.readEntry(tmp, QString()).isEmpty())
			config.writeEntry(tmp, QDate::currentDate().toString());
	}
	config.sync();
}


