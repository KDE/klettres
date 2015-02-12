/***************************************************************************
 *   Copyright (C) 2001-2011 by Anne-Marie Mahfouf                              *
 *   annma@kde.org                                             *
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
#include <QApplication>
#include <QCommandLineParser>

#include <KLocalizedString>
#include <Kdelibs4ConfigMigrator>
#include <kaboutdata.h>
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
    QStringList configFiles;
    configFiles << QLatin1String("klettresrc");
    Kdelibs4ConfigMigrator migrator(QLatin1String("klettres"));
    migrator.setConfigFiles(configFiles);
    migrator.migrate();

    KAboutData about("klettres", i18n("KLettres"), QLatin1String(KLETTRES_VERSION), i18n(description),
                     KAboutLicense::GPL, i18n("(C) 2001-2011 Anne-Marie Mahfouf"),QString(), QLatin1String("http://edu.kde.org/klettres"), QLatin1String("submit@bugs.kde.org"));
    about.addAuthor( i18n("Anne-Marie Mahfouf"), QString(), "annma AT kde DOT org", "http://annma.blogspot.com", "annma");
    about.addCredit(i18n("Marc Cheng"),
                    i18n("Kids and grown-up oxygen icons"), "bdgraue AT web DOT de");
    about.addCredit(i18n("Danny Allen"),
                    i18n("SVG background pictures"), "dannya40uk AT yahoo DOT co DOT uk");
    about.addCredit(i18n("Robert Gogolok"),
                    i18n("Support and coding guidance"), "mail AT robert-gogolok DOT de");
    about.addCredit(i18n("Peter Hedlund"),
                    i18n("Code for generating special characters' icons"), "peter DOT hedlund AT kdemail DOT net");
    about.addCredit(i18n("Waldo Bastian"),
                    i18n("Port to KConfig XT, coding help"), "bastian AT kde DOT org");
    about.addCredit(i18n("Pino Toscano"),
                    i18n("Code cleaning, Theme class"), "toscano DOT pino AT tiscali DOT it");
    about.addCredit(i18n("Michael Goettsche"),
                    i18n("Timer setting widgets"), "michael.goettsche AT kdemail DOT net");
    about.addCredit(i18n("Laurent Navet"),
                    i18n("Port to KDE Frameworks 5"), "laurent DOT navet+klettres AT gmail DOT com");
    QApplication app(argc, argv);
    QCommandLineParser parser;
    KAboutData::setApplicationData(about);
    parser.addVersionOption();
    parser.addHelpOption();
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    app.setApplicationName("klettres");
    app.setApplicationVersion(version);
    app.setOrganizationDomain("kde.org");
    app.setApplicationDisplayName(i18n("Klettres"));

    // see if we are starting with session management
    if (app.isSessionRestored()) {
        RESTORE(KLettres)
    } else {
        // no session.. just start up normally
        if (parser.positionalArguments().count() == 0) {
            KLettres *widget = new KLettres;
            widget->show();
        } else {
            int i = 0;
            for (; i < parser.positionalArguments().count(); i++) {
                KLettres *widget = new KLettres;
                widget->show();
            }
        }
        
    }

    return app.exec();
}

