/* -------------------------------------------------------------
   From KDE Tuberling
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */
 /*
 * Copyright (C) 2001-2004 
   Eric Bischoff
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


#ifndef _SOUNDFACTORY_H_
#define _SOUNDFACTORY_H_

#include <qdom.h>

class KLettres;

/**
 * This class manages the sounds toplay in KLettres, reading the data about the sounds
 * in the sounds.xml file which is in /data.
 *
 * @short Sounds factory class: find and play the right sound.
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 1.1
 */
 
class SoundFactory : public QObject
{
  Q_OBJECT

public:

	SoundFactory(KLettres *parent, const char *name);
	~SoundFactory();
	
	///Change the language when the user changes the language in the Languages menu
	void change(uint selectedLanguage);
	///Play the sound associated to int soundRef
	void playSound(int ) ;
	///Number of sounds corresponding to the current langauge and level (alphabet or syllables)
	uint sounds;
	///List of sound names
	QString *namesList;
	///List of sound files associated with each sound name
	QString *filesList;
	/**
	* Load the sounds of one given language
	* Call that when you read the language from Config and when the language changes
	* or when the level changes
	*/
	bool loadLanguage(QDomDocument &layoutDocument, uint toLoad);

protected:

	///Register the various available languages
	bool registerLanguages(QDomDocument &layoutDocument);

private:
	///Report a load failure
	void loadFailure();

private:
	///Call the main instance of the program
	KLettres *klettres;
	///The language document
  QDomDocument m_layoutsDocument;
};

#endif
