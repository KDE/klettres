/***************************************************************************
 *   Copyright (C) 2001-2007 by Anne-Marie Mahfouf                              *
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

//Qt includes
#include <QBitmap>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QPainter>
#include <QString>
#include <QTextStream>
//KDE includes
#include <kaction.h>
#include <kactioncollection.h>
#include <kcombobox.h>
#include <kconfigdialog.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <knuminput.h>
#include <kselectaction.h>
#include <kstandardaction.h>
#include <kstandarddirs.h>
#include <kstatusbar.h>
#include <ktoggleaction.h>
#include <ktoolbar.h>
#include <kicon.h>
#include <knewstuff2/engine.h>
#include <kapplication.h>

#include <kglobal.h>
//Project includes
#include "klettres.h"
#include "ui_fontsdlg.h"
#include "timer.h"
#include "prefs.h"
#include "langutils.h"

class fontsdlg : public QDialog, public Ui::fontsdlg
{    
    public:
        fontsdlg( QWidget * parent ) : QDialog(parent)
        { setupUi(this); }
};

const int ID_KIDB      = 100;
const int ID_GROWNB    = 101;
const int ID_MENUBARB  = 102;

KLettres::KLettres()
        : KXmlGuiWindow( 0)
{
    setObjectName( QLatin1String("KLettres") );
    mNewStuff = 0;
    m_view = new KLettresView(this);
    // tell the KXmlGuiWindow that this is indeed the main widget
    setCentralWidget(m_view);
    //Scan for existing languages -> m_languages
    m_languages = LangUtils::getLanguages();
    kDebug() << "m_languages  " << m_languages << endl;
    findLanguages();
    Prefs::setLanguage(Prefs::defaultLanguage());
    Prefs::writeConfig();
    //MainWindow GUI: menus, tolbars and statusbar
    setupActions();
    setupStatusbar();
    setupToolbars();
    //Load Settings
    loadSettings();
    //Setup current language sounds
    soundFactory = new SoundFactory(this, "sounds");
    //Start game
    m_view->game();
}

KLettres::~KLettres()
{
}

void KLettres::findLanguages()
{
    m_languageNames.clear();
    //m_sortedNames.clear();
    //the program scans in khangman/data/ to see what languages data is found
    
    //we look in $KDEDIR/share/locale/all_languages from /kdelibs/kdecore/all_languages
    //to find the name of the country
    //corresponding to the code and the language the user set
    KConfig entry(KStandardDirs::locate("locale", "all_languages"));
    const QStringList::ConstIterator itEnd = m_languages.end();
    for (QStringList::Iterator it = m_languages.begin(); it != m_languages.end(); ++it) {
        if (*it == "hi-ro")
            m_languageNames.append(i18n("Romanized Hindi"));
        else if (*it =="lug_UG")
            m_languageNames.append(i18n("Luganda"));
        else
        {
            KConfigGroup group = entry.group(*it);
            m_languageNames.append(group.readEntry("Name"));
        }
    }
    //never sort m_languageNames as it's m_languages translated
    //m_sortedNames = m_languageNames;
}

QString Prefs::defaultLanguage()
{
    //see what is the user language for KDE
    QStringList defaultLanguages = KGlobal::locale()->languagesTwoAlpha();
	if (!defaultLanguages.isEmpty()) {
	//scan to see if defaultLanguages[0] belongs to m_languages. If not, en is default.
	int i = Prefs::self()->m_languages.indexOf(defaultLanguages[0]);
	if (Prefs::self()->m_languages.contains(Prefs::language()))
		return Prefs::language(); //the last language played
	else if (i<1)
		return "en"; //if no other
	else
		return Prefs::self()->m_languages[i]; //KDE default if exists
	}
    return QString();
}


bool KLettres::loadLayout(QDomDocument &layoutDocument)
{
    QFile layoutFile(KStandardDirs::locate("data", "klettres/"+Prefs::language()+"/sounds.xml"));
    //if xml file is not found, program exits
    if (!layoutFile.exists())
    {
        kWarning() << "sounds.xml file not found in $KDEDIR/share/apps/klettres/"+Prefs::language() << endl;
        QString mString=i18n("The file sounds.xml was not found in\n"
                             "$KDEDIR/share/apps/klettres/\n\n"
                             "Please install this file and start KLettres again.\n\n");
        KMessageBox::information( this, mString,"KLettres - Error" );
        qApp->quit();//exit(1);
    }
    if (!layoutFile.open(QIODevice::ReadOnly))
        return false;
    //Check if document is well-formed
    if (!layoutDocument.setContent(&layoutFile))
    {
        layoutFile.close();
        return false;
    }
    layoutFile.close();

    return true;
}

void KLettres::setupActions()
{
    QAction *m_newAction = actionCollection()->addAction("play_new");
    m_newAction->setText(i18n("New Sound"));
    m_newAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_N));
    m_newAction->setIcon(KIcon("file_new"));
    connect(m_newAction, SIGNAL(triggered(bool)), m_view, SLOT(game()));
    m_newAction->setToolTip(i18n("Play a new sound"));
    m_newAction->setWhatsThis(i18n("You can play a new sound by clicking this button or using the File menu, New Sound."));

    QAction *m_stuffAction = actionCollection()->addAction("downloadnewstuff");
    m_stuffAction->setText(i18n("Get Alphabet in New Language..."));
    connect(m_stuffAction, SIGNAL(triggered(bool)),  this, SLOT( slotDownloadNewStuff() ));

    QAction *m_playAgainAction = actionCollection()->addAction("play_again");
    m_playAgainAction->setText(i18n("Replay Sound"));
    m_playAgainAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_P));
    m_playAgainAction->setIcon(KIcon("media-playback-start"));
    m_playAgainAction->setToolTip(i18n("Play the same sound again"));
    connect(m_playAgainAction, SIGNAL(triggered(bool)), m_view, SLOT(slotPlayAgain()));
    m_playAgainAction->setWhatsThis(i18n("You can replay the same sound again by clicking this button or using the File menu, Replay Sound."));
    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());

    m_menubarAction = actionCollection()->add<KToggleAction>("menubar");
    m_menubarAction->setText(i18n("Show &Menubar"));
    m_menubarAction->setIcon(KIcon("edit-clear"));
    m_playAgainAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_M));
    connect(m_menubarAction, SIGNAL(triggered(bool)), this, SLOT(slotMenubar()));
    m_menubarAction->setCheckedState(KGuiItem(i18n("Hide &Menubar")));
    m_menubarAction->setChecked(true);
    m_menubarAction->setWhatsThis(i18n("You can show or hide the menubar as you wish by clicking this button."));

    m_levelAction = actionCollection()->add<KSelectAction>("levels");
    m_levelAction->setText(i18n("L&evel"));
    m_levelAction->setToolTip(i18n("Select the level"));
    m_levelAction->setWhatsThis(i18n("You can select the level: level 1 displays a letter and you hear it; level 2 does not display the letter, you only hear it; level 3 displays a syllable and you hear it; level 4 does not display the syllable, you only hear it."));

    m_languageAction = actionCollection()->add<KSelectAction>("languages");
    m_languageAction->setText(i18n("&Language"));
    m_languageAction->setItems(m_languageNames);

    m_levelsNames.append(i18n( "Level 1" ));
    m_levelsNames.append(i18n( "Level 2" ));
    m_levelsNames.append(i18n( "Level 3" ));
    m_levelsNames.append(i18n( "Level 4" ));
    m_levelAction->setItems(m_levelsNames);

    m_themeAction = actionCollection()->add<KSelectAction>("looks");
    m_themeAction->setText(i18n("Themes"));
    m_themesNames.append(i18n("Classroom"));
    m_themesNames.append(i18n("Arctic"));
    m_themesNames.append(i18n("Desert"));
    m_themeAction->setItems(m_themesNames);
    m_themeAction->setToolTip(i18n("Select the theme"));
    m_themeAction->setWhatsThis(i18n("Here you can change the theme for KLettres. A theme consists in the background picture and the font color for the letter displayed."));

    m_kidAction = actionCollection()->add<KToggleAction>("mode_kid");
    m_kidAction->setText(i18n("Mode Kid"));
    m_kidAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_K));
    m_kidAction->setIcon(KIcon("klettres_kids"));
    connect(m_kidAction, SIGNAL(triggered(bool)), this, SLOT(slotModeKid()));
    m_kidAction->setWhatsThis(i18n("If you are in the Grown-up mode, clicking on this button will set up the Kid mode. The Kid mode has no menubar and the font is bigger in the statusbar."));

    m_grownupAction = actionCollection()->add<KToggleAction>("mode_grownup");
    m_grownupAction->setText(i18n("Mode Grown-up"));
    m_grownupAction->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_G));
    m_grownupAction->setIcon(KIcon("klettres_grownup"));
    connect(m_grownupAction, SIGNAL(triggered(bool)), this, SLOT(slotModeGrownup()));
    m_grownupAction->setWhatsThis(i18n("The Grownup mode is the normal mode where you can see the menubar."));

    connect(m_levelAction, SIGNAL(triggered(int)), this, SLOT(slotChangeLevel(int)));
    connect(m_languageAction, SIGNAL(triggered(int)), this, SLOT(slotChangeLanguage(int)));
    connect(m_themeAction, SIGNAL(triggered(int)), this, SLOT(slotChangeTheme(int)));

    KStandardAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    setupGUI();
}

void KLettres::setupStatusbar()
{
    KStatusBar *st=statusBar();
    m_langLabel = new QLabel(st);
    m_levLabel = new QLabel(st);
    st->addWidget(m_levLabel);
    st->insertFixedItem("", 1);//add a space
    st->addWidget(m_langLabel);
    statusBar();
}

void KLettres::setupToolbars()
{
    //toolbar for special characters
    m_secondToolbar = toolBar("secondToolbar");
    addToolBar ( Qt::BottomToolBarArea, m_secondToolbar);
}

void KLettres::optionsPreferences()
{
    if(KConfigDialog::showDialog("settings"))
        return;

    KConfigDialog *dialog = new KConfigDialog(this, "settings", Prefs::self());
    dialog->addPage(new fontsdlg(0), i18n("Font Settings"), "fonts");
    //fontsdlg is the page name, mFont is the widget name, Font Settings is the page display string
    //fonts is the icon
    Timer *m_timer = new Timer();
    dialog->addPage(m_timer, i18n("Timer"), "clock");
    connect(dialog, SIGNAL(settingsChanged( const QString &)), this, SLOT(slotUpdateSettings()));
    dialog->setAttribute( Qt::WA_DeleteOnClose );
    dialog->show();
}

void KLettres::loadSettings()
{
    //TODO load default language
    //selectedLanguage = Prefs::languageNumber();
    //m_view->selectedLanguage = selectedLanguage;
    m_languageAction->setCurrentItem(Prefs::languageNumber());
    QString langString = m_languageNames[Prefs::languageNumber()];
    langString.replace("&", QString());
    m_langLabel->setText(i18n("Current language is %1", langString));
    loadLangToolBar();
    // load default level
    m_levelAction->setCurrentItem(Prefs::level()-1);
    m_levLabel->setText(i18n("Current level is %1", Prefs::level()));

    if (Prefs::theme() == Prefs::EnumTheme::classroom) {
        m_themeAction->setCurrentItem(0);
        m_view->viewThemeClassroom();
    }
    else if (Prefs::theme() == Prefs::EnumTheme::arctic) {
        m_themeAction->setCurrentItem(1);
        m_view->viewThemeArctic();
    }
    else {
        m_themeAction->setCurrentItem(2);
        m_view->viewThemeDesert();
    }

    if (Prefs::mode() == Prefs::EnumMode::grownup)
        slotModeGrownup();
    else
        slotModeKid();
}

void KLettres::slotDownloadNewStuff()
{
    KNS::Entry::List entries = KNS::Engine::download();
}

void KLettres::slotMenubar()
{
    switch (m_menubarAction->isChecked()){
    case false:
        m_menubarAction->setChecked(false);
        m_menubarAction->setText(i18n("Show Menubar"));
        m_menubarAction->setToolTip(i18n("Show Menubar"));
        menuBar()->hide();
        break;
    case true:
        m_menubarAction->setChecked(true);
        m_menubarAction->setText(i18n("Hide Menubar"));
        m_menubarAction->setToolTip(i18n("Hide Menubar"));
        menuBar()->show();
        break;
    }
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
    Prefs::writeConfig();
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
    m_levLabel->setText(i18n("Current level is %1", Prefs::level()));
}

void KLettres::slotChangeLanguage(int newLanguage)
{
    // Write new language in config
    Prefs::setLanguage(m_languages[newLanguage]);
    Prefs::writeConfig();
    // Update the StatusBar
    QString langString = m_languageNames[newLanguage];
    langString.replace("&", QString());
    m_langLabel->setText(i18n("Current language is %1", langString));
    loadLangToolBar();
    // Change language effectively
    bool ok = loadLayout(soundFactory->m_layoutsDocument);
    if (ok)
        soundFactory->change(Prefs::language());
    m_view->randomInt = 0;
    m_view->game();
}

void KLettres::slotChangeTheme(int index)
{
    switch (index) {
    case 0:
        m_view->viewThemeClassroom();
        break;

    case 1:
        m_view->viewThemeArctic();
        break;

    case 2:
        m_view->viewThemeDesert();
        break;
    }
}

void KLettres::slotModeGrownup()
{
    QPalette pal;
    pal.setColor( QPalette::Background, Qt::white);
    statusBar()->setPalette( pal );
    QFont f_lab( "Serif" , 10);  //font for statusBar
    m_levLabel->setFont(f_lab);
    m_langLabel->setFont(f_lab);
    m_menubarAction->setChecked(true);
    m_grownupAction->setChecked(true);
    m_kidAction->setChecked(false);
    m_grownupAction->setToolTip(i18n("Grown-up mode is currently active"));
    m_kidAction->setToolTip(i18n("Switch to Kid mode"));
    m_menubarAction->setText(i18n("Hide Menubar"));
    m_menubarAction->setToolTip(i18n("Hide Menubar"));
    slotMenubar();
    //m_secondToolbar->setIconSize(22); //causes a crash when adding/removing actions in toolbar
    m_view->m_timer = Prefs::grownTimer();
    Prefs::setMode(Prefs::EnumMode::grownup);
    Prefs::writeConfig();
}

void KLettres::slotModeKid()
{
    QPalette pal;
    pal.setColor( QPalette::Background, Qt::white);
    statusBar()->setPalette( pal );
    QFont f_lab( "Serif" , 12);  //font for statusBar
    f_lab.setBold(true);
    m_levLabel->setFont(f_lab);
    m_langLabel->setFont(f_lab);
    m_menubarAction->setChecked(false);
    slotMenubar();
    m_kidAction->setChecked(true);
    m_kidAction->setToolTip(i18n("Kid mode is currently active"));
    m_grownupAction->setToolTip(i18n("Switch to Grown-up mode"));
    m_menubarAction->setText(i18n("Show Menubar"));
    m_menubarAction->setToolTip(i18n("Show Menubar"));
    m_grownupAction->setChecked(false);
    //m_secondToolbar->setIconSize(32);
    m_view->m_timer = Prefs::kidTimer();
    Prefs::setMode(Prefs::EnumMode::kid);
    Prefs::writeConfig();
}

void KLettres::loadLangToolBar()
{
    m_secondToolbar->clear();
   QString lang = m_languages[Prefs::languageNumber()];
    if (LangUtils::hasSpecialChars(lang))//Dutch, English, French and Italian have no special characters
    {
        allData.clear();
        QString myString=QString("klettres/%1.txt").arg(m_languages[Prefs::languageNumber()]);
        QFile myFile;
        myFile.setFileName(KStandardDirs::locate("data",myString));
        if (!myFile.exists())
        {

            QString mString=i18n("File $KDEDIR/share/apps/klettres/%1.txt not found;\n"
                                    "please check your installation.", m_languages[Prefs::languageNumber()]);
            KMessageBox::sorry( this, mString,
                                    i18n("Error") );
            qApp->quit();
        }
        update();
        //we open the file and store info into the stream...
        QFile openFileStream(myFile.fileName());
        openFileStream.open(QIODevice::ReadOnly);
        QTextStream readFileStr(&openFileStream);
        readFileStr.setCodec("UTF-8");
        //allData contains all the words from the file
        allData = readFileStr.readAll().split("\n");
        openFileStream.close();
        for (int i=0; i<(int) allData.count(); i++) {
            if (!allData[i].isEmpty())
                m_secondToolbar->addAction (charIcon(allData[i].at(0)));//, i, SIGNAL( clicked() ), this, SLOT( slotPasteChar()), true,  i18n("Inserts the character %1").arg(allData[i]), i+1 );
		//TODO fix by creating a new KAction, see KAction API doc
        }
    }
}

void KLettres::slotPasteChar()
{
    QAction *act = qobject_cast<QAction*>(sender());
    if (!act)
        return;

    bool ok = true;
    int id = act->data().toInt(&ok);
    if (!ok || id < 0 || id >= allData.count())
        return;

    m_view->enterLetter(allData.at(id));
}

QString KLettres::charIcon(const QChar & c)
{
    ///Create a name and path for the icon
    QString s = KStandardDirs::locateLocal("icon", "char" + QString::number(c.unicode()) + ".png");

    QRect r(4, 4, 120, 120);

    ///A font to draw the character with
    QFont font;
    font.setFamily( "Arial" );
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

    return s;
}

#include "klettres.moc"