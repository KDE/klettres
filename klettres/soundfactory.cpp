/* -------------------------------------------------------------
   KDE Tuberling
   Play ground widget
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */

#include <stdlib.h>

#include <kmessagebox.h>
#include <klocale.h>
#include <kstandarddirs.h>
#include <kaudioplayer.h>
#include <kdebug.h>

#include <qdom.h>

#include "soundfactory.h"
#include "soundfactory.moc"
#include "klettres.h"

// Constructor
SoundFactory::SoundFactory(KLettres *parent, const char *name, uint selectedLanguage)
	: QObject(parent, name)
{
  klettres = parent;

  namesList = filesList = 0;

  QDomDocument layoutsDocument;
  bool ok = klettres->loadLayout(layoutsDocument);
   if (ok)
  	ok = registerLanguages(layoutsDocument);
  if (ok)
  	ok = loadLanguage(layoutsDocument, selectedLanguage);
  if (!ok) loadFailure();
}

// Destructor
SoundFactory::~SoundFactory()
{
  if (namesList) delete [] namesList;
  if (filesList) delete [] filesList;
}

//When the language changes in KLettres menu
void SoundFactory::change(uint selectedLanguage)
{
  kdDebug() << "in soundFactory, change language " << "language is " << selectedLanguage << endl;
  QDomDocument layoutsDocument;
  bool ok = klettres->loadLayout(layoutsDocument);
  //go load the sounds for the current language
  if (ok) ok = loadLanguage(layoutsDocument, selectedLanguage);
  //tell the user if there are no sounds
  if (!ok) loadFailure();
}

//Play the sound associated to soundRef
void SoundFactory::playSound(int mySound)
{
  QString soundFile;

   if (mySound >= sounds) return;

  soundFile = locate("data", "klettres/" + filesList[mySound]);
  kdDebug() << "File to play:  " << soundFile << endl;

  if (soundFile == 0) return;

  KAudioPlayer::play(soundFile);
}

//Report a load failure
void SoundFactory::loadFailure()
{
	KMessageBox::error(klettres, i18n("Error while loading the sound names."));
}

///Register the various available languages
bool SoundFactory::registerLanguages(QDomDocument &layoutDocument)
{
  QDomNodeList languagesList, menuItemsList, labelsList;
  QDomElement languageElement, menuItemElement, labelElement;
  QDomAttr codeAttribute, actionAttribute;
  bool enabled;
  languagesList = layoutDocument.elementsByTagName("language");
  if (languagesList.count() < 1)
    return false;

  for (uint i = 0; i < languagesList.count(); i++)
  {
    languageElement = (const QDomElement &) languagesList.item(i).toElement();
    codeAttribute = languageElement.attributeNode("code");
    enabled = locate("data", "klettres/" + codeAttribute.value() + "/") != 0;

    menuItemsList = languageElement.elementsByTagName("menuitem");
    if (menuItemsList.count() != 1)
      return false;

    menuItemElement = (const QDomElement &) menuItemsList.item(0).toElement();

    labelsList = menuItemElement.elementsByTagName("label");
    if (labelsList.count() != 1)
      return false;

    labelElement = (const QDomElement &) labelsList.item(0).toElement();
    actionAttribute = menuItemElement.attributeNode("action");

    klettres->registerLanguage(labelElement.text(), actionAttribute.value().latin1(), enabled);
  }

  return true;
}

/*
 * Load the sounds of one given language
 * Call that when you read the language from Config and when the language changes
 * or when the level changes
 */
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

  languageElement = (const QDomElement &) languagesList.item(toLoad).toElement();

  //load the sounds for level 1 and 2 (alphabet)
  if ((klettres->m_view->niveau == 1) || (klettres->m_view->niveau == 2))
  {
 	alphabetList = languageElement.elementsByTagName("alphabet");
    	if (alphabetList.count() != 1)
      		return false;

  	alphabetElement = (const QDomElement &) alphabetList.item(0).toElement();

  	soundNamesList = alphabetElement.elementsByTagName("sound");
        kdDebug() << "In SoundFactory, level 1 or 2 " << endl;
  }

  //load the sounds for level 3 and 4 (syllables)
  if ((klettres->m_view->niveau == 3) || (klettres->m_view->niveau == 4))
  {
 	syllablesList = languageElement.elementsByTagName("syllables");
    	if (syllablesList.count() != 1)
      		return false;

  	syllableElement = (const QDomElement &) syllablesList.item(0).toElement();

  	soundNamesList = syllableElement.elementsByTagName("sound");
        kdDebug() << "In SoundFactory, level 3 or 4 " << endl;
  }
  ///Counts the number of sounds
  sounds = soundNamesList.count();
  kdDebug() << "Number of sounds: " << sounds << endl;
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
    //filesList helds the names of the sound files (i.e the location of the sounds like fr/alpha/a-0.mp3
    filesList[sound] = fileAttribute.value();
  }
  return true;
}

