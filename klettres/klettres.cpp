/*
 * Copyright (C) 2001-2004 Anne-Marie Mahfouf <annma@kde.org>
 *
    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
    */

#include <qbitmap.h>
#include <qpainter.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
//KDE headers
#include <kcombobox.h>
#include <klocale.h>
#include <kdebug.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <kstatusbar.h>
#include <kfiledialog.h>
#include <kedittoolbar.h>
#include <kaction.h>
#include <kconfigdialog.h>
#include <ktoolbarbutton.h>
#include <knuminput.h>
//Project headers
#include "klnewstuff.h"
#include "klettres.h"
#include "fontsdlg.h"
#include "timerdlg.h"
#include "prefs.h"
//standard C++ headers
#include <stdlib.h>
#include <unistd.h>

const int ID_KIDB            = 100;
const int ID_GROWNB     = 101;
const int ID_MENUBARB  = 102;

KLettres::KLettres()
    : KMainWindow( 0, "KLettres" )
{
	m_view = new KLettresView(this);
	// tell the KMainWindow that this is indeed the main widget
	setCentralWidget(m_view);
	mNewStuff = 0;
	// Setup all available sounds
	soundFactory = new SoundFactory(this, "sounds");
	//Read config, must come after SoundFactory, otherwise we don't have all languages
	loadSettings();
	// activate language
	soundFactory->change(selectedLanguage);
	//Set up StatusBar
	KStatusBar *st=statusBar();
	langLabel = new QLabel(st);
	levLabel = new QLabel(st);
	st->addWidget(levLabel);
	st->insertFixedItem("", 1);//add a space
	st->addWidget(langLabel);
	statusBar();
	// then, setup our actions, must be done after loading soundFactory as it has some actions too
	setupActions();
	menuBool=false; //false when menubar button is not shown
	kidBool=false;//false when kid button not shown
	grownBool=false;

	tb = toolBar("mainToolBar");
	//Levels comboBox
	lev_comb= new KComboBox(tb);
	lev_comb->insertItem( i18n( "Level 1" ) );
	lev_comb->insertItem( i18n( "Level 2" ) );
	lev_comb->insertItem( i18n( "Level 3" ) );
	lev_comb->insertItem( i18n( "Level 4" ) );
	tb->insertSeparator(3, 3);
	tb->insertWidget(4, 100, lev_comb, 4); //id, width, widget, index
	connect( lev_comb, SIGNAL( activated(int) ), this, SLOT( slotChangeLevel(int) ) );
	QToolTip::add(lev_comb, i18n("Change the level of difficulty"));
	QWhatsThis::add(lev_comb, i18n( "Use this box to choose the level of difficulty" ));
	tb->insertSeparator(5, 5);

	//toolbar for special characters
	secondToolbar = toolBar("secondToolbar");
	
	//from the Read config, growup is set as default if no style
	if (Prefs::style() == Prefs::EnumStyle::grownup)
		slotGrownup();
	else
		slotKid();

	updateLevMenu(Prefs::level()-1);

	m_view->selectedLanguage = selectedLanguage;
	//write the present languages in config so they cannot be downloaded
	KConfig *config=kapp->config();
	config->setGroup("KNewStuffStatus");
	for (uint i=0;  i<m_languages.count(); i++)
	{
		QString tmp = m_languages[i];
		if (!config->readEntry(tmp))
			config->writeEntry(tmp, QDate::currentDate().toString());
	}
	updateLanguage();

	m_view->game();
}

KLettres::~KLettres()
{
}

void KLettres::setupActions()
{
	new KAction( i18n("Get New Language..."), "knewstuff", 0, this, SLOT( downloadNewStuff() ), actionCollection(), "downloadnewstuff" );
	KStdAction::quit(kapp, SLOT(quit()), actionCollection());

	m_action = new KToggleAction(i18n("Show &Menubar"),CTRL+Key_M, this, SLOT(slotMenubar()), actionCollection(), "menubar");
	m_action->setCheckedState(i18n("Hide &Menubar"));
	m_action->setChecked(true);

	fontAct = new KAction(i18n("Change &Font..."), "fonts", CTRL+Key_F, this, SLOT(optionsPreferences()), actionCollection(), "font");
	timerAct = new KAction(i18n("Set &Timer..."), "clock", CTRL+Key_T, this, SLOT(slotTimer()), actionCollection(), "timer");
	m_languageAction = new KSelectAction(i18n("Language"), KShortcut(), actionCollection(), "languages");
	m_languageAction->setItems(m_languageNames);
	if (selectedLanguage < m_languageNames.count())
		m_languageAction->setCurrentItem(selectedLanguage);

	connect(m_languageAction, SIGNAL(activated(int)), this, SLOT(changeLanguage(int)));

	setupGUI();
}

void KLettres::registerLanguage(const QString &language, const QString &menuItem)
{
	m_languages.append(language);
	//this is for translation of the languages
	KConfig entry(locate("locale", "all_languages"));
	entry.setGroup(language);
	m_languageNames.append(entry.readEntry("Name"));
	Prefs::setLanguages(m_languages);
}

void KLettres::changeLanguage(int newLanguage)
{
	// Do not accept to switch to same language
	if ((uint)newLanguage == selectedLanguage)
		return;
	// Change language in the remembered options
	selectedLanguage = newLanguage;
	// write new language in config file
	Prefs::setLanguageNumber(selectedLanguage);
	Prefs::writeConfig();

	// Update the StatusBar
	updateLanguage();
	// Change language effectively
	soundFactory->change(newLanguage);
	m_view->game();
}

bool KLettres::loadLayout(QDomDocument &layoutDocument)
{
	//QFile layoutFile(QFile::encodeName(locate("data", "klettres/data/sounds.xml")));
	QFile layoutFile(locate("data", "klettres/data/sounds.xml"));
	//if xml file is not found, program exits
	if (!layoutFile.exists())
	{
		kdWarning() << "sounds.xml file not found in $KDEDIR/share/apps/klettres/data/" << endl;
		QString mString=i18n("The file sounds.xml was not found in\n"
					"$KDEDIR/share/apps/klettres/data/\n\n"
					"Please install this file and start KLettres again.\n\n");
		KMessageBox::information( this, mString,"KLettres - Error" );
		exit(1);
	}
	if (!layoutFile.open(IO_ReadOnly))
		return false;
	///Check if document is well-formed
	if (!layoutDocument.setContent(&layoutFile))
	{
		layoutFile.close();
		return false;
	}
	layoutFile.close();

	return true;
}

void KLettres::updateLanguage()
{
	QString langString = m_languageNames[selectedLanguage];
	langString.replace("&", QString::null);
	langLabel->setText(i18n("Current language is %1").arg(langString));
	loadLangToolBar();
}

void KLettres::loadSettings()
{
	selectedLanguage = Prefs::languageNumber();
	//apply the font
	m_view->setFont(Prefs::font());
	if (!kidBool)
		m_view->m_timer = Prefs::kidTimer();
	if (!grownBool)
		m_view->m_timer = Prefs::grownTimer();
}

void KLettres::optionsPreferences()
{
	if(KConfigDialog::showDialog("settings"))
		return;

	KConfigDialog *dialog = new KConfigDialog(this, "settings", Prefs::self());
	dialog->addPage(new fontsdlg(0, "mFont"), i18n("Font Settings"), "fonts");
	//fontsdlg is the page name, mFont is the widget name, Font Settings is the page display string
	//fonts is the icon
	connect(dialog, SIGNAL(settingsChanged()), this, SLOT(loadSettings()));
	dialog->show();
}

void KLettres::slotGrownup()
{
	QPalette pal;
	QColorGroup cg;
	cg.setColor( QColorGroup::Background, white);
	pal.setActive( cg );
	statusBar()->setPalette( pal );
	QFont f_lab( "times" , 12);  //font for statusBar
	levLabel->setFont(f_lab);
	langLabel->setFont(f_lab);
	m_action->setChecked(true);
	slotMenubar();
	if (grownBool) tb->removeItem(ID_GROWNB);
	tb->insertButton ("kids.png", ID_KIDB, SIGNAL( clicked() ), this, SLOT( slotKid()), true, i18n("Switch to the kid look"), 9 );
	kidBool=true;
	m_view->slotGrownup();
	secondToolbar->setIconSize(22);
	setMinimumSize( QSize( 640, 538 ) );
	setMaximumSize( QSize( 640, 538 ) );
	m_view->m_timer = Prefs::grownTimer();
}

void KLettres::slotKid()
{
	QPalette pal;
	QColorGroup cg;
	cg.setColor( QColorGroup::Background, white);
	pal.setActive( cg );
	statusBar()->setPalette( pal );
	QFont f_lab( "times" , 14);  //font for statusBar
	levLabel->setFont(f_lab);
	langLabel->setFont(f_lab);
	m_action->setChecked(false);
	slotMenubar();
	if (kidBool) tb->removeItem(ID_KIDB);
	tb->insertButton ("grownup.png", ID_GROWNB, SIGNAL( clicked() ), this, SLOT( slotGrownup()), true, i18n("Switch to the grown-up look"),10 );
	grownBool=true;
	m_view->slotKid();
	secondToolbar->setIconSize(32);
	setMinimumSize( QSize( 640, 480 ) );
	setMaximumSize( QSize( 640, 480 ) );
	m_view->m_timer = Prefs::kidTimer();
}

void KLettres::slotMenubar()
{
	switch (m_action->isChecked()){
		case false:
			m_action->setChecked(false);
			menuBar()->hide();
			if (menuBool) tb->removeItem(ID_MENUBARB);//check if it is already here. if yes, remove it
			tb->insertButton ("menubar.png", ID_MENUBARB, SIGNAL( clicked() ), this, SLOT( slotShowM()), true, i18n("Show the MenuBar"), 8 );
			menuBool=true;
			break;
		case true:
			m_action->setChecked(true);
			menuBar()->show();
			if (menuBool) tb->removeItem(ID_MENUBARB);
			menuBool=false;//false if no menubar button
			break;
		}
}

void KLettres::slotShowM()
{
	m_action->setChecked(true);
	menuBar()->show();
	if (menuBool) tb->removeItem(ID_MENUBARB);
	menuBool=false;//false if no menubar button
}

void KLettres::slotChangeLevel(int id)
{
	Prefs::setLevel(id+1);
	Prefs::writeConfig();
	updateLevMenu(id);
	//Change level effectively by reloading sounds
	soundFactory->change(selectedLanguage);
	//update game effectively
	m_view->game();
}

void KLettres::updateLevMenu(int id)
{
	lev_comb->setCurrentItem(id);
	levLabel->setText(i18n("Current level is %1").arg(Prefs::level()));
}

void KLettres::loadLangToolBar()
{
	secondToolbar->clear();
	if (m_languages[selectedLanguage]== "cs" || m_languages[selectedLanguage]== "da" || m_languages[selectedLanguage]== "sk")//Dutch, French and Italian have no special characters
	{
		allData.clear();
		QString myString=QString("klettres/%1.txt").arg(m_languages[selectedLanguage]);
		QFile myFile;
		myFile.setName(locate("data",myString));
		if (!myFile.exists())
		{
			QString mString=i18n("File $KDEDIR/share/apps/klettres/%1.txt not found;\n"
						"please check your installation.").arg(m_languages[selectedLanguage]);
			KMessageBox::sorry( this, mString,
						i18n("Error") );
			exit(1);
		}
		update();
		//we open the file and store info into the stream...
		QFile openFileStream(myFile.name());
		openFileStream.open(IO_ReadOnly);
		QTextStream readFileStr(&openFileStream);
		readFileStr.setEncoding(QTextStream::UnicodeUTF8);
		//allData contains all the words from the file
		allData = QStringList::split("\n", readFileStr.read(), true);
		openFileStream.close();
		for (int i=0; i<(int) allData.count(); i++) {
				secondToolbar->insertButton (charIcon(allData[i].at(0)), i, SIGNAL( clicked() ), this, SLOT( slotPasteChar()), true,  i18n("Inserts the character %1").arg(allData[i]), i+1 );
		}
	}
}

void KLettres::slotPasteChar()
{
	KToolBarButton *charBut = (KToolBarButton* ) sender();
	m_view->line1->setText(allData[charBut->id()]);
}

QString Prefs::defaultLanguage()
{
	//see what is the user language for KDE
	QStringList defaultLanguages = KGlobal::locale()->languagesTwoAlpha();
	if (!defaultLanguages.isEmpty())
	return defaultLanguages[0];
	return QString::null;
}

void KLettres::downloadNewStuff()
{
	if ( !mNewStuff )
		mNewStuff = new KLNewStuff( m_view );
 	mNewStuff->download();
}

QString KLettres::charIcon(const QChar & c)
{
	///Create a name and path for the icon
	QString s = locateLocal("icon", "char" + QString::number(c.unicode()) + ".png");

	///No need to redraw if it already exists
	// if (KStandardDirs::exists(s))
	// return s;

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

void KLettres::slotTimer()
{
	if(KConfigDialog::showDialog("timer"))
		return;

	KConfigDialog *dialog = new KConfigDialog(this, "timer", Prefs::self());
	timerdlg *m_timer = new timerdlg();
	dialog->addPage(m_timer, i18n("Timer"), "clock");
	m_timer->kcfg_KidTimer->setRange(0, 20, 2, true);
	m_timer->kcfg_GrownTimer->setRange(0, 20, 2, true);
	connect(dialog, SIGNAL(settingsChanged()), this, SLOT(loadSettings()));
	dialog->show();
}

#include "klettres.moc"
