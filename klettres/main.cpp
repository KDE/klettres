/*
 * Copyright (C) 2001-2004 Anne-Marie Mahfouf <annma@kde.org>
 */
/*****************************************************/
/* Please save with utf8 encoding, thanks  */
/*****************************************************/

#include <dcopclient.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>

#include "klettres.h"
#include "version.h"


static const char description[] =
	I18N_NOOP("KLettres helps a very young child or an adult learning \n"
		  "a new language by associating sounds and \n"
		  "letters in this language.\n"
		  "9 languages are available: Czech, Danish, Dutch, English, French, Italian, Romanized Hindi, Spanish and Slovak.");

static KCmdLineOptions options[] =
{
    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("klettres", I18N_NOOP("KLettres"), KLETTRES_VERSION, description,
                     KAboutData::License_GPL, "(C) 2001-2003 Anne-Marie Mahfouf",0, "http://edu.kde.org/klettres", "submit@bugs.kde.org");
    about.addAuthor( "Anne-Marie Mahfouf", 0, "annma@kde.org");
    about.addCredit("Ludovic Grossard",
            I18N_NOOP("French sounds"), "grossard@kde.org");
    about.addCredit("Geert Stams",
            I18N_NOOP("Dutch sounds"), "geert@pa3csg.myweb.nl");
    about.addCredit("Erik Kjaer Pedersen",
            I18N_NOOP("Danish sounds"), "erik@binghamton.edu");
    about.addCredit("Eva Mikulčíková",
            I18N_NOOP("Czech sounds"), "evmi@seznam.cz");
    about.addCredit("Silvia Motyčková & Jozef Říha",
            I18N_NOOP("Slovak sounds"), "silviamotycka@seznam.cz");
    about.addCredit("Robert Wadley",
             I18N_NOOP("English sounds"), "robntina AT juno DOT com");  
    about.addCredit("Pietro Pasotti",
                I18N_NOOP("Italian sounds"), "pietro@itopen.it");
    about.addCredit("Ana Belén Caballero and Juan Pedro Paredes",
                I18N_NOOP("Spanish sounds"), "neneta@iquis.com");
    about.addCredit("Vikas Kharat",
            I18N_NOOP("Romanized Hindi sounds"), "kharat@sancharnet.in");
    about.addCredit("Primoz Anzur",
            I18N_NOOP("Icons"), "zerokode@yahoo.com");
    about.addCredit("Renaud Blanchard",
            I18N_NOOP("Background picture"), "kisukuma@chez.com");
    about.addCredit("Robert Gogolok",
            I18N_NOOP("Support and coding guidance"), "mail@robert-gogolok.de");
    about.addCredit("Chris Luetchford", 
            I18N_NOOP("svg icon"), "chris@os11.com");
    about.addCredit("Peter Hedlund", 
            I18N_NOOP("Code for generating special characters' icons"), "peter@peterandlinda.com");
    about.addCredit("Waldo Bastian",
        I18N_NOOP("Port to KConfig XT, coding help"), "bastian@kde.org");
    about.addCredit("Danny Allen",
                I18N_NOOP("Kids and grownup svg icons"), "danny@dannyallen.co.uk");
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
