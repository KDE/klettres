/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Wed Oct 17 17:12:06 BST 2001
    copyright            : (C) 2001 by Anne-Marie Mahfouf
    email                : annma@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <kcmdlineargs.h>
#include <kaboutdata.h>
#include <klocale.h>

#include "khsplash.h"

static const char *description =
	I18N_NOOP("KLettres helps a very young child to associate sounds and \n"
                       "letters in his/her language.\n"
						    "2 languages are available: Dutch and French.");
// INSERT A DESCRIPTION FOR YOUR APPLICATION HERE
	
	           	
static KCmdLineOptions options[] =
{
  { 0, 0, 0 }
  // INSERT YOUR COMMANDLINE OPTIONS HERE
};

int main(int argc, char *argv[])
{
  KAboutData aboutData( "klettres", I18N_NOOP("KLettres"),
    VERSION, description, KAboutData::License_GPL,
    "(c) 2001, Anne-Marie Mahfouf", 0, "http://edu.kde.org/klettres", "submit@bugs.kde.org");
  aboutData.addAuthor("Anne-Marie Mahfouf",0, "annma@kde.org");
  aboutData.addCredit("Geert Stams",
	    I18N_NOOP("Dutch sounds"), "gstams.1@hccnet.nl");
  aboutData.addCredit("Primoz Anzur",
	    I18N_NOOP("Splash-screen and icons"), "zerokode@yahoo.com");
  aboutData.addCredit("Renaud Blanchard",
	    I18N_NOOP("Background picture"), "kisukuma@chez.com");
  aboutData.addCredit("Ludovic Grossard",
	    I18N_NOOP("Splash-screen sound"), "ludovic.grossard@libertysurf.fr");
  aboutData.addCredit("Robert Gogolok",
	    I18N_NOOP("Support and coding guidance"), "mail@robert-gogolok.de");
  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options ); // Add our own options.

  KApplication a;
  KhSplash *splash=new KhSplash();
  splash->show();

  return a.exec();
}
