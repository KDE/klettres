/* -------------------------------------------------------------
   from KDE Tuberling
   Sound factory
   mailto:e.bischoff@noos.fr
 ------------------------------------------------------------- */


#ifndef _SOUNDFACTORY_H_
#define _SOUNDFACTORY_H_

#include "qobject.h"

class QDomDocument;
class KLettres;

class SoundFactory : public QObject
{
  Q_OBJECT

public:

  SoundFactory(KLettres *parent, const char *name, uint selectedLanguage);
  ~SoundFactory();

  ///Change the language when the user changes the language in the Languages menu
  void change(uint selectedLanguage);
  ///Play the sound associated to int soundRef
 void playSound(int ) ;
  ///Number of sounds corresponding to the current langauge and level (alphabet or syllables)
  int sounds;
  ///List of sound names
  QString *namesList;
  ///List of sound files associated with each sound name
  QString *filesList;
  ///Load the sounds of one given language
  bool loadLanguage(QDomDocument &layoutDocument, uint toLoad);

protected:

  ///Register the various available languages
  bool registerLanguages(QDomDocument &layoutDocument);

private:
  ///Report a load failure
  void loadFailure();

private:

  KLettres *klettres;
};

#endif
