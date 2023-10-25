/*
    SPDX-FileCopyrightText: 2001-2011 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

/*****************************************************/
/* Please save with utf8 encoding, thanks  */
/*****************************************************/
#include <QApplication>
#include <QCommandLineParser>

#include <KLocalizedString>
#include <KCrash>
#include <KAboutData>
#include "klettres.h"
#include "klettres_version.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("klettres"));

    KAboutData about(QStringLiteral("klettres"), i18n("KLettres"), QStringLiteral(KLETTRES_VERSION_STRING), i18n("KLettres helps a very young child or an adult learning \n"
                                                                                                                 "a new language by associating sounds and \n"
                                                                                                                 "letters in this language.\n\n"
                                                                                                                 "25 languages are available."),
                     KAboutLicense::GPL, i18n("(C) 2001-2011 Anne-Marie Mahfouf"),QString(), QStringLiteral("https://edu.kde.org/klettres"), QStringLiteral("submit@bugs.kde.org"));
    about.addAuthor( i18n("Anne-Marie Mahfouf"), QString(), QStringLiteral("annma AT kde DOT org"), QStringLiteral("https://annma.blogspot.com"), QStringLiteral("annma"));
    about.addCredit(i18n("Marc Cheng"),
                    i18n("Kids and grown-up oxygen icons"), QStringLiteral("bdgraue AT web DOT de"));
    about.addCredit(i18n("Danny Allen"),
                    i18n("SVG background pictures"), QStringLiteral("dannya40uk AT yahoo DOT co DOT uk"));
    about.addCredit(i18n("Robert Gogolok"),
                    i18n("Support and coding guidance"), QStringLiteral("mail AT robert-gogolok DOT de"));
    about.addCredit(i18n("Peter Hedlund"),
                    i18n("Code for generating special characters' icons"), QStringLiteral("peter DOT hedlund AT kdemail DOT net"));
    about.addCredit(i18n("Waldo Bastian"),
                    i18n("Port to KConfig XT, coding help"), QStringLiteral("bastian AT kde DOT org"));
    about.addCredit(i18n("Pino Toscano"),
                    i18n("Code cleaning, Theme class"), QStringLiteral("toscano DOT pino AT tiscali DOT it"));
    about.addCredit(i18n("Michael Goettsche"),
                    i18n("Timer setting widgets"), QStringLiteral("michael.goettsche AT kdemail DOT net"));
    about.addCredit(i18n("Laurent Navet"),
                    i18n("Port to KDE Frameworks 5"), QStringLiteral("laurent DOT navet+klettres AT gmail DOT com"));
    QCommandLineParser parser;
    KAboutData::setApplicationData(about);
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    app.setApplicationName(QStringLiteral("klettres"));
    app.setApplicationVersion(QStringLiteral(KLETTRES_VERSION_STRING));
    app.setOrganizationDomain(QStringLiteral("kde.org"));

    KCrash::initialize();

    // see if we are starting with session management
    if (app.isSessionRestored()) {
        kRestoreMainWindows<KLettres>();
    } else {
        // no session.. just start up normally
        if (parser.positionalArguments().isEmpty()) {
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

