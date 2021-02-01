/***************************************************************************
 *   Copyright 2001-2008 by Anne-Marie Mahfouf                              *
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

#include "klettres.h"
#include <kwidgetsaddons_version.h>

//Qt includes
#include <QAction>
#include <QBitmap>
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QStatusBar>
#include <QIcon>
#include <QTextStream>
#include <QMenuBar>
#include <QDomDocument>
#include <QWidget>
#include <QStandardPaths>
#include <QPointer>

//KDE includes
#include <KActionCollection>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KMessageBox>
#include <KSelectAction>
#include <KStandardAction>
#include <KToolBar>
#include <KToggleAction>

#include <kns3/downloaddialog.h>
//Project includes
#include "ui_fontsdlg.h"
#include "timer.h"
#include "prefs.h"
#include "langutils.h"
#include "kltheme.h"

class fontsdlg : public QWidget, public Ui::fontsdlg
{
    public:
        fontsdlg( QWidget * parent ) : QWidget(parent)
        {
            setupUi(this);
        }
};

const int ID_KIDB      = 100;
const int ID_GROWNB    = 101;
const int ID_MENUBARB  = 102;

KLettres::KLettres()
        : KXmlGuiWindow( nullptr )
{
    setObjectName( QStringLiteral("KLettres") );
    mNewStuff = nullptr;
    m_view = new KLettresView(this);
    setMinimumSize( QSize( 800, 600 ) );
    //Tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);
    //Populate Languages menu with m_languageNames
    m_languageNames = LangUtils::getLanguagesNames(LangUtils::getLanguages());
    //MainWindow GUI: menus, tolbars and statusbar
    setupActions();
    setupStatusbar();
    setupToolbars();
    //Load Settings
    loadSettings();
    //Setup current language sounds
    soundFactory = new SoundFactory(this, QStringLiteral("sounds"));
    //Start game
    m_view->game();
}

KLettres::~KLettres()
{
}

bool KLettres::loadLayout(QDomDocument &layoutDocument)
{
    QFile layoutFile(QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                        QStringLiteral("klettres/")+Prefs::language()+QStringLiteral("/sounds.xml")));

    //if xml file is not found, program exits
    if (!layoutFile.exists()) {
        qWarning() << "sounds.xml file not found in $KDEDIR/share/apps/klettres/" << Prefs::language() ;
        QString mString=i18n("The file sounds.xml was not found in\n"
                             "$KDEDIR/share/apps/klettres/\n\n"
                             "Please install this file and start KLettres again.\n\n");
        KMessageBox::information( this, mString,i18n("KLettres - Error") );
        qApp->quit();//exit(1);
    }

    if (!layoutFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    //Check if document is well-formed
    if (!layoutDocument.setContent(&layoutFile)) {
        layoutFile.close();
        return false;
    }

    layoutFile.close();

    return true;
}

void KLettres::setupActions()
{
    QAction *m_newAction = actionCollection()->addAction(QStringLiteral("play_new"));
    m_newAction->setText(i18n("New Sound"));
    actionCollection()->setDefaultShortcut(m_newAction,QKeySequence(Qt::CTRL+Qt::Key_N));
    m_newAction->setIcon(QIcon::fromTheme(QStringLiteral("document-new"))); // ### better icon for this?
    connect(m_newAction, &QAction::triggered, m_view, &KLettresView::game);
    m_newAction->setToolTip(i18n("Play a new sound"));
    m_newAction->setWhatsThis(i18n("You can play a new sound by clicking this button or using the File menu, New Sound."));

    QAction *m_stuffAction = actionCollection()->addAction(QStringLiteral("downloadnewstuff"));
    m_stuffAction->setText(i18n("Get Alphabet in New Language..."));
    m_stuffAction->setIcon(QIcon::fromTheme(QStringLiteral("get-hot-new-stuff")));
    connect(m_stuffAction, &QAction::triggered, this, &KLettres::slotDownloadNewStuff);

    QAction *m_playAgainAction = actionCollection()->addAction(QStringLiteral("play_again"));
    m_playAgainAction->setText(i18n("Replay Sound"));
    actionCollection()->setDefaultShortcut(m_playAgainAction,QKeySequence(Qt::Key_F5));
    m_playAgainAction->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-start")));
    m_playAgainAction->setToolTip(i18n("Play the same sound again"));
    connect(m_playAgainAction, &QAction::triggered, m_view, &KLettresView::slotPlayAgain);
    m_playAgainAction->setWhatsThis(i18n("You can replay the same sound again by clicking this button or using the File menu, Replay Sound."));
    KStandardAction::quit(qApp, SLOT(quit()), actionCollection());

    m_menubarAction = KStandardAction::showMenubar(this, SLOT(slotMenubar()), actionCollection());

    m_levelAction = actionCollection()->add<KSelectAction>(QStringLiteral("levels"));
    m_levelAction->setText(i18nc("@label:listbox which difficulty level to use", "L&evel"));
    m_levelAction->setToolTip(i18n("Select the level"));
    m_levelAction->setWhatsThis(i18n("You can select the level: level 1 displays a letter and you hear it; level 2 does not display the letter, you only hear it; level 3 displays a syllable and you hear it; level 4 does not display the syllable, you only hear it."));

    m_languageAction = actionCollection()->add<KSelectAction>(QStringLiteral("languages"));
    m_languageAction->setText(i18nc("@label:listbox", "&Language"));
    m_languageAction->setItems(m_languageNames);

    m_levelsNames.append(i18ncp("@item:inlistbox choose level", "Level %1" , "Level %1", 1));
    m_levelsNames.append(i18ncp("@item:inlistbox choose level", "Level %1" , "Level %1", 2));
    m_levelsNames.append(i18ncp("@item:inlistbox choose level", "Level %1" , "Level %1", 3));
    m_levelsNames.append(i18ncp("@item:inlistbox choose level", "Level %1" , "Level %1", 4));
    m_levelAction->setItems(m_levelsNames);
    m_levelAction->setCurrentItem(Prefs::level()-1);

    m_themeAction = actionCollection()->add<KSelectAction>(QStringLiteral("looks"));
    m_themeAction->setText(i18n("Themes"));
    m_themeAction->setItems(KLThemeFactory::instance()->themeList());
    m_themeAction->setCurrentItem(Prefs::theme());
    m_themeAction->setToolTip(i18n("Select the theme"));
    m_themeAction->setWhatsThis(i18n("Here you can change the theme for KLettres. A theme consists in the background picture and the font color for the letter displayed."));

    m_kidAction = actionCollection()->add<KToggleAction>(QStringLiteral("mode_kid"));
    m_kidAction->setText(i18n("Mode Kid"));
    actionCollection()->setDefaultShortcut(m_kidAction,QKeySequence(Qt::CTRL+Qt::Key_K));
    m_kidAction->setIcon(QIcon::fromTheme(QStringLiteral("klettres_kids")));
    connect(m_kidAction, &KToggleAction::triggered, this, &KLettres::slotModeKid);
    m_kidAction->setWhatsThis(i18n("If you are in the Grown-up mode, clicking on this button will set up the Kid mode. The Kid mode has no menubar and the font is bigger in the statusbar."));

    m_grownupAction = actionCollection()->add<KToggleAction>(QStringLiteral("mode_grownup"));
    m_grownupAction->setText(i18n("Mode Grown-up"));
    actionCollection()->setDefaultShortcut(m_grownupAction,QKeySequence(Qt::CTRL+Qt::Key_G));
    m_grownupAction->setIcon(QIcon::fromTheme(QStringLiteral("klettres_grownup")));
    connect(m_grownupAction, &KToggleAction::triggered, this, &KLettres::slotModeGrownup);
    m_grownupAction->setWhatsThis(i18n("The Grownup mode is the normal mode where you can see the menubar."));

#if KWIDGETSADDONS_VERSION < QT_VERSION_CHECK(5, 78, 0)
    connect(m_levelAction, static_cast<void (KSelectAction::*)(int)>(&KSelectAction::triggered), this, &KLettres::slotChangeLevel);
#else
    connect(m_levelAction, &KSelectAction::indexTriggered, this, &KLettres::slotChangeLevel);
#endif
#if KWIDGETSADDONS_VERSION < QT_VERSION_CHECK(5, 78, 0)
    connect(m_languageAction, static_cast<void (KSelectAction::*)(int)>(&KSelectAction::triggered), this, &KLettres::slotChangeLanguage);
#else
    connect(m_languageAction, &KSelectAction::indexTriggered, this, &KLettres::slotChangeLanguage);
#endif
#if KWIDGETSADDONS_VERSION < QT_VERSION_CHECK(5, 78, 0)
    connect(m_themeAction, static_cast<void (KSelectAction::*)(int)>(&KSelectAction::triggered), this, &KLettres::slotChangeTheme);
#else
    connect(m_themeAction, &KSelectAction::indexTriggered, this, &KLettres::slotChangeTheme);
#endif

    KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    setupGUI();
}

void KLettres::setupStatusbar()
{
    QStatusBar *st=statusBar();
    m_langLabel = new QLabel(st);
    m_levLabel = new QLabel(st);
    st->addWidget(m_langLabel);
//    st->insertFixedItem("", 1);//add a space
    st->addWidget(m_levLabel);
    statusBar();
}

void KLettres::setupToolbars()
{
    // Toolbar for special characters
    specialCharToolbar = toolBar(QStringLiteral("specialCharToolbar"));
    addToolBar ( Qt::BottomToolBarArea, specialCharToolbar);
}

void KLettres::optionsPreferences()
{
    if(KConfigDialog::showDialog(QStringLiteral("settings"))) {
        return;
    }

    KConfigDialog *dialog = new KConfigDialog(this, QStringLiteral("settings"), Prefs::self());
    dialog->addPage(new fontsdlg(nullptr), i18n("Font"), QStringLiteral("preferences-desktop-font"), i18n("Font Settings"));
    //fontsdlg is the page name, mFont is the widget name, Font Settings is the page display string
    //fonts is the icon
    Timer *m_timer = new Timer();
    dialog->addPage(m_timer, i18n("Timer"), QStringLiteral("chronometer"), i18n("Timer Settings"));
    connect(dialog, &KConfigDialog::settingsChanged, this, &KLettres::slotUpdateSettings);
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    // dialog->setHelp(QString(), "klettres");
    dialog->show();
}

void KLettres::loadSettings()
{
    if (LangUtils::getLanguages().indexOf(Prefs::language()) < 0)  {
        Prefs::setLanguage(QStringLiteral("en"));
    }
    QString langString = LangUtils::getLanguagesNames(LangUtils::getLanguages())[LangUtils::getLanguages().indexOf(Prefs::language())];
    m_languageAction->setCurrentItem(LangUtils::getLanguages().indexOf(Prefs::language()));
    langString.remove(QLatin1Char('&'));
    m_langLabel->setText(langString);
    loadLangToolBar();
    // load default level
    m_levLabel->setText(i18nc("@info:status the current level chosen", "(Level %1)", Prefs::level()));

    m_view->setTheme(KLThemeFactory::instance()->buildTheme(Prefs::theme()));

    if (Prefs::mode() == Prefs::EnumMode::grownup) {
        slotModeGrownup();
    } else {
        slotModeKid();
    }

    m_menubarAction->setChecked(Prefs::menuBarBool());
    slotMenubar();
}

void KLettres::slotDownloadNewStuff()
{
    QPointer<KNS3::DownloadDialog> dialog(new KNS3::DownloadDialog(QStringLiteral("klettres.knsrc"), this));
    if ( dialog->exec() == QDialog::Accepted ) {
        // do nothing
    }

    delete dialog;

    //look for languages dirs installed
    QStringList languages = LangUtils::getLanguages();
    m_languageNames = LangUtils::getLanguagesNames(languages);

    //refresh Languages menu
    m_languageAction->setItems(m_languageNames);
    slotChangeLanguage(languages.indexOf(Prefs::language()));
    m_languageAction->setCurrentItem(languages.indexOf(Prefs::language()));
}

void KLettres::slotMenubar()
{
    menuBar()->setVisible(m_menubarAction->isChecked());
    Prefs::setMenuBarBool(m_menubarAction->isChecked());
    Prefs::self()->save();
}

void KLettres::slotUpdateSettings()
{
    m_view->m_timer = Prefs::kidTimer();
    m_view->m_timer = Prefs::grownTimer();
    //apply the font
    m_view->setFont(Prefs::font());
}

void KLettres::slotChangeLevel(int newLevel)
{
    Prefs::setLevel(newLevel+1);
    Prefs::self()->save();
    updateLevMenu(newLevel);
    //TODO is that necessary? Change level effectively by reloading sounds

    //this is duplicated in changeLanguage()
    soundFactory->change(Prefs::language());
    //update game effectively
    m_view->randomInt = 0;
    m_view->game();
}

void KLettres::updateLevMenu(int id)
{
    //m_levelCombo->setCurrentItem(id);
    m_levelAction->setCurrentItem(id);
    m_levLabel->setText(i18nc("@info:status the current level chosen", "(Level %1)", Prefs::level()));
}

void KLettres::slotChangeLanguage(int newIndex)
{
    // Write new language ISO in config
    QString newLanguage = LangUtils::getLanguages()[newIndex];
    Prefs::setLanguage(newLanguage);
    Prefs::self()->save();
    // Update the StatusBar
    QString langString = LangUtils::getLanguagesNames(LangUtils::getLanguages())[newIndex];
    langString.remove(QLatin1Char('&'));
    m_langLabel->setText(langString);
    loadLangToolBar();
    // Change language effectively
    bool ok = loadLayout(soundFactory->m_layoutsDocument);

    if (ok) {
        soundFactory->change(Prefs::language());
    }

    m_view->randomInt = 0;
    m_view->game();
}

void KLettres::slotChangeTheme(int index)
{
    Prefs::setTheme(index);
    Prefs::self()->save();
    m_view->setTheme(KLThemeFactory::instance()->buildTheme(index));
}

void KLettres::slotModeGrownup()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Qt::white);
    statusBar()->setPalette( pal );
    QFont f_lab( QStringLiteral("Serif") , 10);  //font for statusBar
    m_levLabel->setFont(f_lab);
    m_langLabel->setFont(f_lab);
    m_menubarAction->setChecked(true);
    m_grownupAction->setChecked(true);
    m_kidAction->setChecked(false);
    m_grownupAction->setToolTip(i18n("Grown-up mode is currently active"));
    m_kidAction->setToolTip(i18n("Switch to Kid mode"));
    menuBar()->show();
    m_view->m_timer = Prefs::grownTimer();
    Prefs::setMode(Prefs::EnumMode::grownup);
    Prefs::self()->save();
}

void KLettres::slotModeKid()
{
    QPalette pal;
    pal.setColor( QPalette::Window, Qt::white);
    statusBar()->setPalette( pal );
    QFont f_lab( QStringLiteral("Serif") , 12);  //font for statusBar
    f_lab.setBold(true);
    m_levLabel->setFont(f_lab);
    m_langLabel->setFont(f_lab);
    m_menubarAction->setChecked(false);
    m_kidAction->setChecked(true);
    m_kidAction->setToolTip(i18n("Kid mode is currently active"));
    m_grownupAction->setToolTip(i18n("Switch to Grown-up mode"));
    m_grownupAction->setChecked(false);
    menuBar()->hide();
    m_view->m_timer = Prefs::kidTimer();
    Prefs::setMode(Prefs::EnumMode::kid);
    Prefs::self()->save();
}

void KLettres::loadLangToolBar()
{
    QString lang = Prefs::language();

    specialCharToolbar->clear();

    if (LangUtils::hasSpecialChars(lang)) {//Dutch, English, French and Italian have no special characters
        allData.clear();
        QString myString=QStringLiteral("klettres/%1.txt").arg(lang);
        QFile myFile;
        myFile.setFileName(QStandardPaths::locate(QStandardPaths::GenericDataLocation, myString));

        if (!myFile.exists()) {
            QString mString=i18n("File $KDEDIR/share/apps/klettres/%1.txt not found;\n"
                                    "please check your installation.", lang);
            KMessageBox::sorry( this, mString,
                                    i18n("Error") );
            qApp->quit();
        }

        //we open the file and store info into the stream...
        QFile openFileStream(myFile.fileName());
        openFileStream.open(QIODevice::ReadOnly);
        QTextStream readFileStr(&openFileStream);
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
        readFileStr.setCodec("UTF-8");
#endif
        //allData contains all the words from the file
        allData = readFileStr.readAll().split(QLatin1Char('\n'));
        openFileStream.close();

        for (int i=0; i<(int) allData.count(); ++i) {
            if (!allData[i].isEmpty()) {
                QAction *act = specialCharToolbar->addAction(allData.at(i));
                act->setIcon(charIcon(allData.at(i).at(0)));
                // used to carry the id
                act->setData(i);
                connect(act, &QAction::triggered, this, &KLettres::slotPasteChar);
            }
        }

        specialCharToolbar->show();
        update();
    } else {
      specialCharToolbar->hide();
    }
}

void KLettres::slotPasteChar()
{
    QAction *act = qobject_cast<QAction*>(sender());
    if (!act) {
        return;
    }

    bool ok = true;
    int id = act->data().toInt(&ok);

    if (!ok || id < 0 || id >= allData.count()) {
        return;
    }

    m_view->m_letterEdit->insert(allData.at(id));
}

QIcon KLettres::charIcon(QChar c)
{
    ///Create a name and path for the icon
    //
    // FIXME: This code used KStandardDirs::locateLocal("icon", ...) before
    //        and I am not sure if GenericCacheLocation is what we are aiming
    //        for.  So best would be if somebody experienced in QStandardPaths
    //        could confirm or change it.

    QString s = QStandardPaths::locate(QStandardPaths::GenericCacheLocation,
                                       QStringLiteral("char") + QString::number(c.unicode()) + QStringLiteral(".png"));

    QRect r(4, 4, 120, 120);

    ///A font to draw the character with
    QFont font;
    font.setFamily( QStringLiteral("Arial") );
    font.setPixelSize(120);
    font.setWeight(QFont::Normal);

    ///Create the pixmap
    QPixmap pm(128, 128);
    pm.fill(Qt::white);
    QPainter p(&pm);
    p.setFont(font);
    p.setPen(Qt::black);
    p.drawText(r, Qt::AlignCenter, (QString) c);

    ///Create transparency mask
    QBitmap bm(128, 128);
    bm.fill(Qt::color0);
    QPainter b(&bm);
    b.setFont(font);
    b.setPen(Qt::color1);
    b.drawText(r, Qt::AlignCenter, (QString) c);

    ///Mask the pixmap
    pm.setMask(bm);

    ///Save the icon to disk
    pm.save(s, "PNG");

    return QIcon(pm);
}


