/* -------------------------------------------------------------
   From KDE Tuberling
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */
/*
 * Copyright (C) 2001-2004 Eric Bischoff
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
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
#include <stdlib.h>

#include <kmessagebox.h>
#include <klocale.h>
#include <kaudioplayer.h>
#include <kdebug.h>

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
	if (ok)
		ok = registerLanguages(m_layoutsDocument);
	if (!ok) loadFailure();
}

SoundFactory::~SoundFactory()
{
	if (namesList) delete [] namesList;
	if (filesList) delete [] filesList;
}

void SoundFactory::change(uint selectedLanguage)
{
	//go load the sounds for the current language
	bool ok = loadLanguage(m_layoutsDocument, selectedLanguage);
	//tell the user if there are no sounds
	if (!ok) loadFailure();
}

void SoundFactory::playSound(int mySound)
{
	QString soundFile;
	
	if ((uint) mySound >= sounds) return;
	
	soundFile = locate("data", "klettres/" + filesList[mySound]);
	
	if (soundFile == 0) return;
	
	KAudioPlayer::play(soundFile);
}

void SoundFactory::loadFailure()
{
	KMessageBox::error(klettres, i18n("Error while loading the sound names."));
}

bool SoundFactory::registerLanguages(QDomDocument &layoutDocument)
{
	QDomNodeList languagesList, menuItemsList, labelsList;
	QDomElement languageElement, menuItemElement, labelElement;
	QDomAttr codeAttribute, actionAttribute;
	bool enabled;
	//languagesList: "languages" tags from sounds.xml
	languagesList = layoutDocument.elementsByTagName("language");
	if (languagesList.count() < 1)
		return false;
	
	for (uint i = 0; i < languagesList.count(); i++)
	{
		languageElement = (const QDomElement &) languagesList.item(i).toElement();
		codeAttribute = languageElement.attributeNode("code");
		//here it looks in $KDEDIR/share/apps/klettres and in $KDEHOME/share/apps/klettres
		enabled = locate("data", "klettres/" + codeAttribute.value() + "/") != 0;
		menuItemsList = languageElement.elementsByTagName("menuitem");
		if (menuItemsList.count() != 1)
			return false;
		
		menuItemElement = (const QDomElement &) menuItemsList.item(0).toElement();
		
		labelsList = menuItemElement.elementsByTagName("label");
		if (labelsList.count() != 1)
			return false;
		
		labelElement = (const QDomElement &) labelsList.item(0).toElement();
		
		if (enabled)
			klettres->registerLanguage(codeAttribute.value(), labelElement.text());
	}
	
	return true;
}

bool SoundFactory::loadLanguage(QDomDocument &layoutDocument, uint toLoad)
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
	if (toLoad >= languagesList.count())
		return false;

	QDomAttr codeAttribute;
	//find the language in the list
	for (uint i = 0; i < languagesList.count(); i++)
	{
		languageElement = (const QDomElement &) languagesList.item(i).toElement();
		codeAttribute = languageElement.attributeNode("code");
		if (codeAttribute.value() == klettres->m_languages[toLoad])
			break;		
	}
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
	
	if (!(namesList = new QString[sounds]))
		return false;
	if (!(filesList = new QString[sounds]))
		return false;
	
	for (uint sound = 0; sound < sounds; sound++)
	{
		soundNameElement = (const QDomElement &) soundNamesList.item(sound).toElement();
		nameAttribute = soundNameElement.attributeNode("name");
		//namesList helds the names of the letter or syllable to display
		namesList[sound] = nameAttribute.value();
		fileAttribute = soundNameElement.attributeNode("file");
		//filesList helds the names of the sound files (i.e the location of the sounds like fr/alpha/a-0.mp3)
		filesList[sound] = fileAttribute.value();
	}
	return true;
}

