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
#include "klettres_debug.h"

#include <QDir>

#include <KLocalizedString>

bool LangUtils::hasSpecialChars(const QString& lang)
{
    if (lang== QLatin1String("cs")
        || lang== QLatin1String("da")
        || lang== QLatin1String("sk")
        || lang== QLatin1String("es")
        || lang== QLatin1String("de")
        || lang== QLatin1String("hu")
        || lang== QLatin1String("nds")
        || lang== QLatin1String("lt"))
        return true;
    return false;
}

bool LangUtils::isIndian(const QString& lang)
{
    if (lang == QLatin1String("kn")
        || lang == QLatin1String("ml")
        || lang == QLatin1String("te")
        || lang == QLatin1String("pa"))
        return true;
    return false;
}

QStringList LangUtils::getLanguages()
{
    QStringList m_languages;
    m_languages.clear();
    //the program scans in klettres/data/ to see what languages data is found
    const QStringList mdirs = QStandardPaths::locateAll(QStandardPaths::GenericDataLocation,
							QStringLiteral("klettres/"),
							QStandardPaths::LocateDirectory);
    //qDebug() << mdirs;

    //if (mdirs.isEmpty()) return NULL;
    for (QStringList::const_iterator it =mdirs.constBegin(); it !=mdirs.constEnd(); ++it ) {
        QDir dir(*it);
        m_languages += dir.entryList(QDir::Dirs, QDir::Name);
        m_languages.removeAll(QStringLiteral("."));
        m_languages.removeAll(QStringLiteral(".."));
    }
    m_languages.removeAll(QStringLiteral("pics"));
    m_languages.removeAll(QStringLiteral("data"));
    m_languages.removeAll(QStringLiteral("icons"));
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
    qCDebug(KLETTRES_LOG) <<m_languages;
    return m_languages;
}

QStringList LangUtils::getLanguagesNames(const QStringList &languagesList)
{
    QStringList languagesNames;

    for (const QString &language : languagesList) {
        if (language == QLatin1String("hi-ro")) {
            languagesNames.append(i18n("Romanized Hindi"));
        } else if (language == QLatin1String("lug_UG")) {
            languagesNames.append(i18n("Luganda"));
        } else if (language == QLatin1String("ep")) {
            languagesNames.append(i18n("English Phonics"));
        } else if (language == QLatin1String("tn")) {
            languagesNames.append(i18n("Tswana"));
        } else {
            QLocale locale(language);
            QString languageName = locale.nativeLanguageName();
            if (locale == QLocale::c())
                languageName = i18nc("@item:inlistbox no language for that locale", "None");
            languagesNames.append(languageName);
        }
    }
    //never sort m_languageNames as it's m_languages translated
    return languagesNames;
}

void LangUtils::writeLangConfig()
{
    //write the present languages in config so they cannot be downloaded
    KConfigGroup config(KSharedConfig::openConfig(), "KNewStuffStatus");
    QStringList m_languages = getLanguages();
    for (int i=0;  i<m_languages.count(); i++)  {
        QString tmp = m_languages[i];
        if (!config.readEntry(tmp, QString()).isEmpty()) {
            config.writeEntry(tmp, QDate::currentDate().toString());
        }
    }
    config.sync();
}


