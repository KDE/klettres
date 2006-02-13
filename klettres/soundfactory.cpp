/* -------------------------------------------------------------
   From KDE Tuberling
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */
/*
 * Copyright (C) 2001 Eric Bischoff
   2004-2006 Anne-Marie Mahfouf <annma@kde.org>

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
#include <stdlib.h>

#include <kmessagebox.h>
#include <klocale.h>
#include <kaudioplayer.h>
#include <kdebug.h>
#include <kstandarddirs.h>

#include "soundfactory.h"
#include "soundfactory.moc"
#include "klettres.h"
#include "prefs.h"


SoundFactory::SoundFactory(KLettres *parent, const char *name)
        : QObject(parent, name)
{
    klettres = parent;

    namesList = filesList = 0;
    sounds = 0;

    bool ok = klettres->loadLayout(m_layoutsDocument);
    if (ok) change(Prefs::language());
    if (!ok) loadFailure();
}

SoundFactory::~SoundFactory()
{
}

void SoundFactory::change(QString currentLanguage)
{
    //go load the sounds for the current language
    bool ok = loadLanguage(m_layoutsDocument, currentLanguage);
    kdDebug() << "ok " << ok << endl;
    //tell the user if there are no sounds
    if (!ok) loadFailure();
}

void SoundFactory::playSound(int mySound)
{
    QString soundFile;

    if ((uint) mySound >= sounds) return;

    soundFile = locate("data", "klettres/" + filesList[mySound]);
    kdDebug() << "soundFile " << soundFile << endl;
    
    if (soundFile == 0) return;
    
    KAudioPlayer::play(soundFile);
}

void SoundFactory::loadFailure()
{
    KMessageBox::error(klettres, i18n("Error while loading the sound names."));
}

bool SoundFactory::loadLanguage(QDomDocument &layoutDocument, QString currentLanguage)
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

    languagesList = layoutDocument.elementsByTagName("language");
    QDomAttr codeAttribute;
    //check if the sound files match current language
    languageElement = (const QDomElement &) languagesList.item(0).toElement();
    codeAttribute = languageElement.attributeNode("code");
    if (currentLanguage != codeAttribute.value()) {
        kdDebug() << "Fail reading language !!! " << endl;
        return false;
    }
    else kdDebug() << "current language " << currentLanguage << endl;
    //load the sounds for level 1 and 2 (alphabet)
    if ((Prefs::level() == 1) || (Prefs::level() == 2))
    {
        alphabetList = languageElement.elementsByTagName("alphabet");
        if (alphabetList.count() != 1)
            return false;

        alphabetElement = (const QDomElement &) alphabetList.item(0).toElement();

        soundNamesList = alphabetElement.elementsByTagName("sound");
    }

    //load the sounds for level 3 and 4 (syllables)
    if ((Prefs::level() == 3) || (Prefs::level() == 4))
    {
        syllablesList = languageElement.elementsByTagName("syllables");
        if (syllablesList.count() != 1)
            return false;

        syllableElement = (const QDomElement &) syllablesList.item(0).toElement();

        soundNamesList = syllableElement.elementsByTagName("sound");
    }
    //Counts the number of sounds
    sounds = soundNamesList.count();
    if (sounds < 1)
        return false;

   namesList.clear();
   filesList.clear();

    for (uint sound = 0; sound < sounds; sound++)
    {
        soundNameElement = (const QDomElement &) soundNamesList.item(sound).toElement();
        nameAttribute = soundNameElement.attributeNode("name");
        //namesList helds the names of the letter or syllable to display
        namesList.append(nameAttribute.value());
        fileAttribute = soundNameElement.attributeNode("file");
        //filesList helds the names of the sound files (i.e the location of the sounds like fr/alpha/a-0.mp3)
        filesList.append(fileAttribute.value());
    }
    if (namesList.isEmpty())   return false;
    if (filesList.isEmpty())   return false;
    return true;
}

