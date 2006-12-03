/***************************************************************************
 *   Copyright (C) 2001-2005 by Anne-Marie Mahfouf                              *
 *   annemarie.mahfouf@free.fr                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.             *
 ***************************************************************************/

/*****************************************************/
/* Please save with utf8 encoding, thanks  */
/*****************************************************/

#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <kapplication.h>

#include "klettres.h"
#include "version.h"

static const char description[] =
    I18N_NOOP("KLettres helps a very young child or an adult learning \n"
              "a new language by associating sounds and \n"
              "letters in this language.\n"
              "13 languages are available: British, Czech, Danish, Dutch, English, French,\nGerman, Hebrew, Italian, Luganda, Romanized Hindi, Spanish and Slovak.");

static const char version[] = "1.5.1";

static KCmdLineOptions options[] =
    {
        //    { "+[URL]", I18N_NOOP( "Document to open" ), 0 },
        KCmdLineLastOption
    };

int main(int argc, char **argv)
{
    KAboutData about("klettres", I18N_NOOP("KLettres"), KLETTRES_VERSION, description,
                     KAboutData::License_GPL, "(C) 2001-2006 Anne-Marie Mahfouf",0, "http://edu.kde.org/klettres", "submit@bugs.kde.org");
    about.addAuthor( "Anne-Marie Mahfouf", 0, "annma AT kde.org");
    about.addCredit("Ludovic Grossard",
                    I18N_NOOP("French sounds"), "grossard AT kde.org");
    about.addCredit("Geert Stams",
                    I18N_NOOP("Dutch sounds"), "geert AT pa3csg.myweb.nl");
    about.addCredit("Erik Kjaer Pedersen",
                    I18N_NOOP("Danish sounds"), "erik AT binghamton.edu");
    about.addCredit("Eva Mikulčíková",
                    I18N_NOOP("Czech sounds"), "evmi AT seznam.cz");
    about.addCredit("Silvia Motyčková & Jozef Říha",
                    I18N_NOOP("Slovak sounds"), "silviamotycka AT seznam.cz");
    about.addCredit("Robert Wadley",
                    I18N_NOOP("English sounds"), "robntina AT juno DOT com");               
    about.addCredit("Pietro Pasotti",
                    I18N_NOOP("Italian sounds"), "pietro AT itopen.it");
    about.addCredit("Ana Belén Caballero and Juan Pedro Paredes",
                    I18N_NOOP("Spanish sounds"), "neneta  AT iquis.com");
    about.addCredit("Vikas Kharat",
                    I18N_NOOP("Romanized Hindi sounds"), "kharat AT sancharnet.in");
    about.addCredit("John Magoye and Cormac Lynch",
                     I18N_NOOP("Luganda sounds"), "cormaclynch AT eircom.net");
    about.addCredit("Helmut Kriege",
                     I18N_NOOP("German sounds"), "h.kriege AT freenet.de");
    about.addCredit("Assaf Gorgon and Diego Iastrubni",
                     I18N_NOOP("Hebrew sounds"), "elcuco AT kde.org");
    about.addCredit("Lisa Kriege",
                     I18N_NOOP("British English sounds"), "h.kriege AT freenet.de");
    about.addCredit("Primoz Anzur",
                    I18N_NOOP("Icons"), "zerokode AT yahoo.com");
    about.addCredit("Renaud Blanchard",
                    I18N_NOOP("Background picture"), "kisukuma AT chez.com");
    about.addCredit("Robert Gogolok",
                    I18N_NOOP("Support and coding guidance"), "mail AT robert-gogolok.de");
    about.addCredit("Chris Luetchford",
                    I18N_NOOP("SVG icon"), "chris AT os11.com");
    about.addCredit("Peter Hedlund",
                    I18N_NOOP("Code for generating special characters' icons"), "peter.hedlund AT kdemail.net");
    about.addCredit("Waldo Bastian",
                    I18N_NOOP("Port to KConfig XT, coding help"), "bastian AT kde.org");
    about.addCredit("Danny Allen",
                    I18N_NOOP("Kids and grown-up SVG icons"), "danny AT dannyallen.co.uk");
    about.addCredit("Michael Goettsche",
                    I18N_NOOP("Timer setting widgets"), "michael.goettsche AT kdemail.net");
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

