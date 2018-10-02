/* -------------------------------------------------------------
   From KDE Tuberling
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */
 /*
 * Copyright (C) 2001 Eric Bischoff <e.bischoff@noos.fr>
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


#ifndef _SOUNDFACTORY_H_
#define _SOUNDFACTORY_H_

#include <QObject>
#include <QStringList>
#include <QDomDocument>

class KLettres;
namespace Phonon
{
    class MediaObject;
}

/**
 * This class manages the sounds to play in KLettres, reading the data about the sounds
 * in the sounds.xml file which is in /data.
 *
 * @short Sounds factory class: find and play the right sound.
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 1.80
 */
 
class SoundFactory : public QObject
{
  Q_OBJECT

public:

    explicit SoundFactory(KLettres *parent, const QString &name);
    ~SoundFactory();

    ///Call the main instance of the program
    KLettres *klettres;
    ///Change the language when the user changes the language in the Languages menu
    void change(const QString &currentLanguage);
    ///Play the sound associated to int soundRef
    void playSound(int ) ;
    ///Number of sounds corresponding to the current language and level (alphabet or syllables)
    uint sounds;
    ///List of sound names
    QStringList namesList;
    ///List of sound files associated with each sound name
    QStringList filesList;
    /**
    * Load the sounds of one given language
    * Call that when you read the language from Config and when the language changes
    * or when the level changes
    */
    bool loadLanguage(QDomDocument &layoutDocument, const QString &currentLanguage);
    ///The language document
    QDomDocument m_layoutsDocument;
    ///The random sequence of integers
    QList<int> randomList;

private:
    ///Report a load failure
    void loadFailure();
    ///Shuffle the index in random to get random sounds. The sequence of random sounds will take 1 random sound after another, then restart when all sounds have been played
    void setSoundSequence();
    Phonon::MediaObject *m_player;
};

#endif
