/***************************************************************************
 *   Copyright (C) 2001-2006 by Anne-Marie Mahfouf                              *
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
#include <QToolTip>
#include <QWhatsThis>
#include <QTextStream>
//KDE includes
#include <kaction.h>
#include <kapplication.h>
#include <kcombobox.h>
#include <kconfigdialog.h>
#include <kdebug.h>
#include <klocale.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <knuminput.h>
#include <kselectaction.h>
#include <kstdaction.h>
#include <kstandarddirs.h>
#include <kstatusbar.h>
#include <ktoggleaction.h>
#include <ktoolbar.h>

#include <kglobal.h>
//Project includes
#include "klnewstuff.h"
#include "klettres.h"
#include "fontsdlg.h"
#include "timer.h"
#include "prefs.h"

const int ID_KIDB      = 100;
const int ID_GROWNB    = 101;
const int ID_MENUBARB  = 102;

KLettres::KLettres()
        : KMainWindow( 0, "KLettres" )
{
    mNewStuff = 0;
    m_view = new KLettresView(this);
    // tell the KMainWindow that this is indeed the main widget
    setCentralWidget(m_view);
    //Scan for existing languages -> m_languages
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
    setMinimumSize( QSize( 640, 550 ) );
    setMaximumSize( QSize( 640, 550 ) );
    //Start game
    m_view->game();
}

KLettres::~KLettres()
{
}

void KLettres::findLanguages()
{
    m_languages.clear();
    m_languageNames.clear();
    //m_sortedNames.clear();
    //the program scans in khangman/data/ to see what languages data is found
    QStringList mdirs = KGlobal::dirs()->findDirs("data", "klettres/");
    if (mdirs.isEmpty()) return;
    for (QStringList::Iterator it =mdirs.begin(); it !=mdirs.end(); ++it ) {
        QDir dir(*it);
        m_languages += dir.entryList(QDir::Dirs, QDir::Name);
        m_languages.removeAll(".");
        m_languages.removeAll("..");
    }
    m_languages.removeAll("pics");
    m_languages.removeAll("data");
    m_languages.removeAll("icons");
    m_languages.sort();
    if (m_languages.isEmpty()) return;
    Prefs::setLanguages(m_languages);
    Prefs::writeConfig();
    //find duplicated entries in KDEDIR and KDEHOME
    QStringList temp_languages;
    for (int i=0;  i<m_languages.count(); i++)
    {
        if (m_languages.count(m_languages[i])>1) {
            temp_languages.append(m_languages[i]);
            m_languages.removeAll(m_languages[i]);
        }
	for (int i=0;  i<temp_languages.count(); i++)
	{
		if (i%2==0)
		m_languages.append(temp_languages[i]);//append 1 of the 2 instances found
	}
    temp_languages.clear();
    }
//TODO TEST in FRENCH
    m_languages.sort();
    //write the present languages in config so they cannot be downloaded
    KConfig *config=KGlobal::config();
    config->setGroup("KNewStuffStatus");
    for (int i=0;  i<m_languages.count(); i++)
    {
        QString tmp = m_languages[i];
        if (!config->readEntry(tmp, QString()).isEmpty())
            config->writeEntry(tmp, QDate::currentDate().toString());
    }
    //we look in $KDEDIR/share/locale/all_languages from /kdelibs/kdecore/all_languages
    //to find the name of the country
    //corresponding to the code and the language the user set
    KConfig entry(locate("locale", "all_languages"));
    const QStringList::ConstIterator itEnd = m_languages.end();
    for (QStringList::Iterator it = m_languages.begin(); it != m_languages.end(); ++it) {
        if (*it == "hi-ro")
            m_languageNames.append(i18n("Romanized Hindi"));
        else if (*it =="lug_UG")
            m_languageNames.append(i18n("Luganda"));
        else
        {
            entry.setGroup(*it);
            m_languageNames.append(entry.readEntry("Name"));
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
        if (i<1)
            return "en";
        else
            return defaultLanguages[0];
    }
    return QString();
}


bool KLettres::loadLayout(QDomDocument &layoutDocument)
{
    QFile layoutFile(locate("data", "klettres/"+Prefs::language()+"/sounds.xml"));
    //if xml file is not found, program exits
    if (!layoutFile.exists())
    {
        kWarning() << "sounds.xml file not found in $KDEDIR/share/apps/klettres/"+Prefs::language() << endl;
        QString mString=i18n("The file sounds.xml was not found in\n"
                             "$KDEDIR/share/apps/klettres/\n\n"
                             "Please install this file and start KLettres again.\n\n");
        KMessageBox::information( this, mString,"KLettres - Error" );
        kapp->quit();//exit(1);
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
    KAction *m_newAction = new KAction(i18n("New Sound"), actionCollection(), "play_new");
    m_newAction->setShortcut(Qt::CTRL+Qt::Key_N);
    m_newAction->setIcon(KIcon("file_new"));
    connect(m_newAction, SIGNAL(triggered(bool)), m_view, SLOT(game()));
    m_newAction->setToolTip(i18n("Play a new sound"));
    m_newAction->setWhatsThis(i18n("You can play a new sound by clicking this button or using the File menu, New Sound.")); 

    KAction *m_stuffAction = new KAction(i18n("Get Alphabet in New Language..."), actionCollection(), "downloadnewstuff");
    connect(m_stuffAction, SIGNAL(triggered(bool)),  this, SLOT( slotDownloadNewStuff() ));

    KAction *m_playAgainAction = new KAction(i18n("Replay Sound"),  actionCollection(), "play_again");
    m_playAgainAction->setShortcut(Qt::CTRL+Qt::Key_P);
    m_playAgainAction->setIcon(KIcon("player_play"));	
    m_playAgainAction->setToolTip(i18n("Play the same sound again"));
    connect(m_playAgainAction, SIGNAL(triggered(bool)), m_view, SLOT(slotPlayAgain()));
    m_playAgainAction->setWhatsThis(i18n("You can replay the same sound again by clicking this button or using the File menu, Replay Sound."));
    KStdAction::quit(kapp, SLOT(quit()), actionCollection());

    m_menubarAction = new KToggleAction(i18n("Show &Menubar"),  actionCollection(), "menubar");
    m_menubarAction->setIcon(KIcon("editclear"));
    m_playAgainAction->setShortcut(Qt::CTRL+Qt::Key_M);
    connect(m_menubarAction, SIGNAL(triggered(bool)), this, SLOT(slotMenubar()));
    m_menubarAction->setCheckedState(i18n("Hide &Menubar"));
    m_menubarAction->setChecked(true);
    m_menubarAction->setWhatsThis(i18n("You can show or hide the menubar as you wish by clicking this button."));

    m_levelAction = new KSelectAction(i18n("L&evel"), actionCollection(), "levels");
    m_levelAction->setToolTip(i18n("Select the level"));
    m_levelAction->setWhatsThis(i18n("You can select the level: level 1 displays a letter and you hear it; level 2 does not display the letter, you only hear it; level 3 displays a syllable and you hear it; level 4 does not display the syllable, you only hear it."));

    m_languageAction = new KSelectAction(i18n("&Language"), actionCollection(), "languages");
    m_languageAction->setItems(m_languageNames);

    m_levelsNames.append(i18n( "Level 1" ));
    m_levelsNames.append(i18n( "Level 2" ));
    m_levelsNames.append(i18n( "Level 3" ));
    m_levelsNames.append(i18n( "Level 4" ));
    m_levelAction->setItems(m_levelsNames);

    m_themeAction =  new KSelectAction(i18n("Themes"), actionCollection(), "looks");
    m_themesNames.append(i18n("Classroom"));
    m_themesNames.append(i18n("Arctic"));
    m_themesNames.append(i18n("Desert"));
    m_themeAction->setItems(m_themesNames);
    m_themeAction->setToolTip(i18n("Select the theme"));
    m_themeAction->setWhatsThis(i18n("Here you can change the theme for KLettres. A theme consists in the background picture and the font color for the letter displayed."));

    m_kidAction = new KToggleAction(i18n("Mode Kid"), actionCollection(), "mode_kid");
    m_kidAction->setShortcut(Qt::CTRL+Qt::Key_K);
    m_kidAction->setIcon(KIcon("klettres_kids"));
    connect(m_kidAction, SIGNAL(triggered(bool)), this, SLOT(slotModeKid()));
    m_kidAction->setWhatsThis(i18n("If you are in the Grown-up mode, clicking on this button will set up the Kid mode. The Kid mode has no menubar and the font is bigger in the statusbar."));

    m_grownupAction = new KToggleAction(i18n("Mode Grown-up"), actionCollection(), "mode_grownup");
    m_grownupAction->setShortcut(Qt::CTRL+Qt::Key_G);
    m_grownupAction->setIcon(KIcon("klettres_grownup"));
    connect(m_grownupAction, SIGNAL(triggered(bool)), this, SLOT(slotModeGrownup()));
    m_grownupAction->setWhatsThis(i18n("The Grownup mode is the normal mode where you can see the menubar."));

    connect(m_levelAction, SIGNAL(triggered(int)), this, SLOT(slotChangeLevel(int)));
    connect(m_languageAction, SIGNAL(triggered(int)), this, SLOT(slotChangeLanguage(int)));
    connect(m_themeAction, SIGNAL(triggered(int)), this, SLOT(slotChangeTheme(int)));

    KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

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
    dialog->addPage(new fontsdlg(0, "mFont"), i18n("Font Settings"), "fonts");
    //fontsdlg is the page name, mFont is the widget name, Font Settings is the page display string
    //fonts is the icon
    Timer *m_timer = new Timer();
    dialog->addPage(m_timer, i18n("Timer"), "clock");
    connect(dialog, SIGNAL(settingsChanged( const QString &)), this, SLOT(slotUpdateSettings()));
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
    if ( !mNewStuff )
        mNewStuff = new KLNewStuff( m_view );
    mNewStuff->download();
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
    QColorGroup cg;
    cg.setColor( QPalette::Background, Qt::white);
    //pal.setActive( cg );
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
    setMinimumSize( QSize( 640, 538 ) );
    setMaximumSize( QSize( 640, 538 ) );
    m_view->m_timer = Prefs::grownTimer();
    Prefs::setMode(Prefs::EnumMode::grownup);
    Prefs::writeConfig();
}

void KLettres::slotModeKid()
{
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QPalette::Background, Qt::white);
    //pal.setActive( cg );
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
    setMinimumSize( QSize( 640, 480 ) );
    setMaximumSize( QSize( 640, 480 ) );
    m_view->m_timer = Prefs::kidTimer();
    Prefs::setMode(Prefs::EnumMode::kid);
    Prefs::writeConfig();
}

void KLettres::loadLangToolBar()
{
    m_secondToolbar->clear();
    if (m_languages[Prefs::languageNumber()]== "cs" || m_languages[Prefs::languageNumber()]== "da" || m_languages[Prefs::languageNumber()]== "sk" || m_languages[Prefs::languageNumber()]== "es")//Dutch, English, French and Italian have no special characters
    {
        allData.clear();
        QString myString=QString("klettres/%1.txt").arg(m_languages[Prefs::languageNumber()]);
        QFile myFile;
        myFile.setFileName(locate("data",myString));
        if (!myFile.exists())
        {
        
            QString mString=i18n("File $KDEDIR/share/apps/klettres/%1.txt not found;\n"
                                    "please check your installation.", m_languages[Prefs::languageNumber()]);
            KMessageBox::sorry( this, mString,
                                    i18n("Error") );
            kapp->quit();
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
#warning "kde4: port it";
#if 0		
        QToolButton *charBut = (QToolButton* ) sender();
        m_view->m_letterEdit->setText(allData[charBut->id()]);
#endif		
}

QString KLettres::charIcon(const QChar & c)
{
    ///Create a name and path for the icon
    QString s = locateLocal("icon", "char" + QString::number(c.unicode()) + ".png");

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
