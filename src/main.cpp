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
              "25 languages are available.");

static const char version[] = "2.1";

int main(int argc, char **argv)
{
    KAboutData about("klettres", 0, ki18n("KLettres"), KLETTRES_VERSION, ki18n(description),
                     KAboutData::License_GPL, ki18n("(C) 2001-2011 Anne-Marie Mahfouf"),KLocalizedString(), "http://edu.kde.org/klettres", "submit@bugs.kde.org");
    about.addAuthor( ki18n("Anne-Marie Mahfouf"), KLocalizedString(), "annma AT kde DOT org", "http://annma.blogspot.com", "annma");
    about.addCredit(ki18n("Marc Cheng"),
                    ki18n("Kids and grown-up oxygen icons"), "bdgraue AT web DOT de");
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
    if (app.isSessionRestored()) {
        RESTORE(KLettres)
    } else {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
        if (args->count() == 0) {
            KLettres *widget = new KLettres;
            widget->show();
        } else {
            int i = 0;
            for (; i < args->count(); i++) {
                KLettres *widget = new KLettres;
                widget->show();
            }
        }
        args->clear();
    }

    return app.exec();
}

