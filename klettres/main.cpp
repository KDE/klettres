/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>

#include "klettres.h"
#include "version.h"


static const char description[] =
	I18N_NOOP("KLettres helps a very young child or an adult learning \n"
		  "a new language by associating sounds and \n"
		  "letters in this language.\n"
		  "4 languages are available: Czech, Danish, Dutch and French.");

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open." ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("klettres", I18N_NOOP("KLettres"), KLETTRES_VERSION, description,
                     KAboutData::License_GPL, "(C) 2001-2003 Anne-Marie Mahfouf",0, "http://edu.kde.org/klettres", "submit@bugs.kde.org");
    about.addAuthor( "Anne-Marie Mahfouf,", 0, "annma@kde.org");
    about.addCredit("Ludovic Grossard",
	    I18N_NOOP("French sounds"), "grossard@kde.org");
    about.addCredit("Geert Stams",
	    I18N_NOOP("Dutch sounds"), "geert@pa3csg.myweb.nl");
    about.addCredit("Erik Kjaer Pedersen",
	    I18N_NOOP("Danish sounds"), "erik@binghamton.edu");
    about.addCredit("Eva Mikulčíková",
	    I18N_NOOP("Czech sounds"), "eva@seznam.cz");
   about.addCredit("Eva Mikulčíková & Jozef Riha",
	    I18N_NOOP("Slovak sounds"), "eva@seznam.cz");
    about.addCredit("Primoz Anzur",
	    I18N_NOOP("Icons"), "zerokode@yahoo.com");
    about.addCredit("Renaud Blanchard",
	    I18N_NOOP("Background picture"), "kisukuma@chez.com");
    about.addCredit("Robert Gogolok",
	    I18N_NOOP("Support and coding guidance"), "mail@robert-gogolok.de");
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    // see if we are starting with session management
    if (app.isRestored())
        RESTORE(KLettres)
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0)
        {
            KLettres *widget = new KLettres;
            widget->show();
        }
        else
        {
            int i = 0;
            for (; i < args->count(); i++)
            {
                KLettres *widget = new KLettres;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}
