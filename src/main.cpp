/***************************************************************************
 *   Copyright (C) 2001-2008 by Anne-Marie Mahfouf                              *
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
#include <klocale.h>
#include <kapplication.h>
#include "klettres.h"
#include "version.h"

static const char description[] =
    I18N_NOOP("KLettres helps a very young child or an adult learning \n"
              "a new language by associating sounds and \n"
              "letters in this language.\n\n"
              "18 languages are available: Arabian, Brazilian Portuguese, British, Czech, Danish, Dutch, English, French, German, Hebrew, Italian, Kannada, Low Saxon, Luganda, Romanized Hindi, Spanish, Slovak and Telugu.");

static const char version[] = "2.1";

int main(int argc, char **argv)
{
    KAboutData about("klettres", 0, ki18n("KLettres"), KLETTRES_VERSION, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2001-2008 Anne-Marie Mahfouf"),KLocalizedString(), "http://edu.kde.org/klettres", "submit@bugs.kde.org");
    about.addAuthor( ki18n("Anne-Marie Mahfouf"), KLocalizedString(), "annma AT kde DOT org");
    about.addCredit(ki18n("Marc Cheng"),
                    ki18n("Kids and grown-up oxygen icons"), "bdgraue AT web DOT de");
    about.addCredit(ki18n("Ludovic Grossard"),
                    ki18n("French sounds"), "grossard AT kde DOT org");
    about.addCredit(ki18n("Geert Stams"),
                    ki18n("Dutch sounds"), "geert AT pa3csg DOT myweb DOT nl");
    about.addCredit(ki18n("Erik Kjaer Pedersen"),
                    ki18n("Danish sounds"), "erik AT binghamton DOT edu");
    about.addCredit(ki18n("Eva Mikulčíková"),
                    ki18n("Czech sounds"), "evmi AT seznam DOT cz");
    about.addCredit(ki18n("Silvia Motyčková & Jozef Říha"),
                    ki18n("Slovak sounds"), "silviamotycka AT seznam DOT cz");
    about.addCredit(ki18n("Robert Wadley"),
                    ki18n("English sounds"), "robntina AT juno DOT com");               
    about.addCredit(ki18n("Pietro Pasotti"),
                    ki18n("Italian sounds"), "pietro AT itopen DOT it");
    about.addCredit(ki18n("Ana Belén Caballero and Juan Pedro Paredes"),
                    ki18n("Spanish sounds"), "neneta  AT iquis DOT com");
    about.addCredit(ki18n("Vikas Kharat"),
                    ki18n("Romanized Hindi sounds"), "kharat AT sancharnet DOT in");
    about.addCredit(ki18n("John Magoye and Cormac Lynch"),
                     ki18n("Luganda sounds"), "cormaclynch AT eircom DOT net");
    about.addCredit(ki18n("Helmut Kriege"),
                     ki18n("German sounds"), "h.kriege AT freenet DOT de");
    about.addCredit(ki18n("Assaf Gorgon and Diego Iastrubni"),
                     ki18n("Hebrew sounds"), "elcuco AT kde DOT org");
    about.addCredit(ki18n("Lisa Kriege"),
                     ki18n("British English sounds"), "h.kriege AT freenet DOT de");
    about.addCredit(ki18n("Vikram Vincent"),
                     ki18n("Kannada sounds"), "vincentvikram AT gmail DOT com");
    about.addCredit(ki18n("Danny Allen"),
                    ki18n("SVG background pictures"), "dannya40uk AT yahoo DOT co DOT uk");
    about.addCredit(ki18n("Robert Gogolok"),
                    ki18n("Support and coding guidance"), "mail AT robert-gogolok DOT de");
    about.addCredit(ki18n("Peter Hedlund"),
                    ki18n("Code for generating special characters' icons"), "peter DOT hedlund AT kdemail DOT net");
    about.addCredit(ki18n("Waldo Bastian"),
                    ki18n("Port to KConfig XT, coding help"), "bastian AT kde DOT org");
    about.addCredit(ki18n("Pino Toscano"),
                    ki18n("Code cleaning, Theme class"), "toscano DOT pino AT tiscali DOT it");
    about.addCredit(ki18n("Michael Goettsche"),
                    ki18n("Timer setting widgets"), "michael.goettsche AT kdemail DOT net");
    KCmdLineArgs::init(argc, argv, &about);

    KCmdLineOptions options;
    KCmdLineArgs::addCmdLineOptions(options);
    KApplication app;

    // see if we are starting with session management
    if (app.isSessionRestored())
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

