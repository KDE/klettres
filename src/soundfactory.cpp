/* -------------------------------------------------------------
   From KDE Tuberling
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */
/*
 * Copyright (C) 2001 Eric Bischoff
   2004-2007 Anne-Marie Mahfouf <annma@kde.org>

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

#include "soundfactory.h"

#include <QStandardPaths>

#include <KMessageBox>
#include <KLocalizedString>
#include <KRandomSequence>
#include <phonon/MediaObject>

#include "klettres_debug.h"
#include "klettres.h"
#include "prefs.h"

SoundFactory::SoundFactory(KLettres *parent, const QString &name)
        : QObject(parent), m_player(nullptr)
{
    setObjectName(name);
    klettres = parent;

    namesList.clear();
    filesList.clear();
    sounds = 0;

    bool ok = klettres->loadLayout(m_layoutsDocument);
    if (ok)  {
        change(Prefs::language());
    }
    if (!ok)  {
        loadFailure();
    }  else  {
        setSoundSequence();
    }
}

SoundFactory::~SoundFactory()
{
}

void SoundFactory::change(const QString &currentLanguage)
{
    //go load the sounds for the current language
    bool ok = loadLanguage(m_layoutsDocument, currentLanguage);
    //tell the user if there are no sounds or get the random sounds
    if (!ok)  {
        loadFailure();
    }  else  {
        setSoundSequence();
    }
}

void SoundFactory::playSound(int mySound)
{
    QString soundFile;

    if ((uint) mySound >= sounds) {
        return;
    }

    soundFile = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                       QStringLiteral("klettres/") + filesList[mySound]);
    qCDebug(KLETTRES_LOG) << "soundFile " << soundFile;

    if (soundFile.isEmpty()) {
        return;
    }

    if (!m_player)  {
        m_player = Phonon::createPlayer(Phonon::GameCategory, QUrl::fromLocalFile(soundFile));
        m_player->setParent(this);
    }  else  {
        m_player->setCurrentSource(QUrl::fromLocalFile(soundFile));
    }
    m_player->play();
}

void SoundFactory::loadFailure()
{
    KMessageBox::error(klettres, i18n("Error while loading the sound names."));
    klettres->slotChangeLevel(Prefs::level()-1);
    bool ok = loadLanguage(m_layoutsDocument, Prefs::language());
    if (ok)  {
        change(Prefs::language());
    }
}

bool SoundFactory::loadLanguage(QDomDocument &layoutDocument, const QString &currentLanguage)
{
    QDomNodeList languagesList,
    alphabetList,
    syllablesList,
    soundNamesList;
    QDomElement languageElement,
    alphabetElement,
    syllableElement,
    soundNameElement;
    QDomAttr nameAttribute, fileAttribute;

    languagesList = layoutDocument.elementsByTagName(QStringLiteral("language"));
    QDomAttr codeAttribute;
    //check if the sound files match current language
    languageElement = (const QDomElement &) languagesList.item(0).toElement();
    codeAttribute = languageElement.attributeNode(QStringLiteral("code"));

    if (currentLanguage != codeAttribute.value()) {
        qCDebug(KLETTRES_LOG) << "Fail reading language !!! ";
        return false;
    } else {
        qCDebug(KLETTRES_LOG) << "current language " << currentLanguage;
    }
    //check here if alphabet and syllables both exist
    alphabetList = languageElement.elementsByTagName(QStringLiteral("alphabet"));
    syllablesList = languageElement.elementsByTagName(QStringLiteral("syllables"));

    //load the sounds for level 1 and 2 (alphabet)
    if ((Prefs::level() == 1) || (Prefs::level() == 2))  {
        if (alphabetList.count() != 1) {
            return false;
        }
        alphabetElement = (const QDomElement &) alphabetList.item(0).toElement();
        soundNamesList = alphabetElement.elementsByTagName(QStringLiteral("sound"));
    }

    //load the sounds for level 3 and 4 (syllables)
    if ((Prefs::level() == 3) || (Prefs::level() == 4))  {
        if (syllablesList.count() != 1) {
            Prefs::setLevel(1);
            Prefs::self()->save();
            return false;
        }

        syllableElement = (const QDomElement &) syllablesList.item(0).toElement();

        soundNamesList = syllableElement.elementsByTagName(QStringLiteral("sound"));
    }
    //Counts the number of sounds
    sounds = soundNamesList.count();
    qCDebug(KLETTRES_LOG) << "number of sounds" << sounds;
    if (sounds < 1)  {
        return false;
    }
    namesList.clear();
    filesList.clear();

    for (uint sound = 0; sound < sounds; sound++)  {
        soundNameElement = (const QDomElement &) soundNamesList.item(sound).toElement();
        nameAttribute = soundNameElement.attributeNode(QStringLiteral("name"));
        //namesList helds the names of the letter or syllable to display
        namesList.append(nameAttribute.value());
        fileAttribute = soundNameElement.attributeNode(QStringLiteral("file"));
        //filesList helds the names of the sound files (i.e the location of the sounds like fr/alpha/a-0.mp3)
        filesList.append(fileAttribute.value());
    }
    if (namesList.isEmpty()) {
        return false;
    }
    if (filesList.isEmpty())  {
        return false;
    }
    return true;
}

void SoundFactory::setSoundSequence()
{
    // Seed the random number generator
    KRandomSequence randomSequence;
    randomList.clear();
    //get the number of sounds then shuffle it: each number will be taken once then the sequence will come back
    for (uint j = 0; j < sounds; j++) 
        randomList.append(j);

    randomSequence.randomize(randomList);
}


