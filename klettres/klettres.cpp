/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
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

    /****************************************/
    /* Please save as utf8 encoding */
    /****************************************/
#include <qtooltip.h>
#include <qwhatsthis.h>
//KDE headers
#include <kcombobox.h>
#include <klocale.h>
#include <kdebug.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <kstatusbar.h>
#include <kkeydialog.h>
#include <kfiledialog.h>
#include <kedittoolbar.h>
#include <kaction.h>
#include <kfontdialog.h>
#include <kconfigdialog.h>
//Project headers
#include "klnewstuff.h"
#include "klettres.h"
#include "fontsdlg.h"
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
	KConfig *cfg = KGlobal::config();
	cfg->setGroup("KNewStuff");
	cfg->writeEntry( "ProvidersUrl", "http://edu.kde.org/klettres/downloads/providers.xml" );
	cfg->sync();
	// Setup all available sounds
	soundFactory = new SoundFactory(this, "sounds");
	//Read config, must come after SoundFactory, otherwise we don't have all languages
	loadSettings();
	// activate language
	soundFactory->change(selectedLanguage);
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
	//Set up StatusBar
	KStatusBar *st=statusBar();
	langLabel = new QLabel(st);
	levLabel = new QLabel(st);
	st->addWidget(levLabel);
	st->insertFixedItem("", 1);//add a space
	st->addWidget(langLabel);
	statusBar();
	//from the Read config, growup is set as default if no style
	if (Prefs::style() == Prefs::EnumStyle::grownup)
		slotGrownup();
	else
		slotKid();
	
	updateLevMenu(Prefs::level()-1);
	
	m_view->selectedLanguage = selectedLanguage;
	updateLanguage();
	
	m_view->game();
}

KLettres::~KLettres()
{
}

void KLettres::setupActions()
{
	//KGlobal::iconLoader()->loadIcon("knewstuff", KIcon::Small);
	new KAction( i18n("Get a new language..."), "knewstuff", 0, this, SLOT( downloadNewStuff() ), actionCollection(), "downloadnewstuff" );
	KStdAction::quit(kapp, SLOT(quit()), actionCollection());
	
	m_action = new KToggleAction(i18n("Show &Menubar"),CTRL+Key_M, this, SLOT(slotMenubar()), actionCollection(), "menubar");
	m_action->setChecked(true);
	
	createStandardStatusBarAction();
	setStandardToolBarMenuEnabled(true);
	
	KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
	KStdAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
	fontAct = new KAction(i18n("Change &Font..."), "fonts", CTRL+Key_F, this, SLOT(optionsPreferences()), actionCollection(), "font");
	
	m_languageAction = new KSelectAction(i18n("Language"), KShortcut(), actionCollection(), "languages");
	m_languageAction->setItems(m_languageNames);
	if (selectedLanguage < m_languageNames.count())
	m_languageAction->setCurrentItem(selectedLanguage);
	
	connect(m_languageAction, SIGNAL(activated(int)), this, SLOT(changeLanguage(int)));
	
	setAutoSaveSettings("General");
	createGUI();
}

// Register an available language
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
	if (newLanguage == selectedLanguage)
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

void KLettres::optionsConfigureKeys()
{
    	KKeyDialog::configure(actionCollection());
}

void KLettres::optionsConfigureToolbars()
{
	// use the standard toolbar editor
	saveMainWindowSettings( KGlobal::config(), autoSaveGroup() );
	KEditToolbar dlge(actionCollection());
	connect(&dlge, SIGNAL(newToolbarConfig()), this, SLOT(newToolbarConfig()));
	dlge.exec();
}

void KLettres::newToolbarConfig()
{
	// this slot is called when user clicks "Ok" or "Apply" in the toolbar editor.
	// recreate our GUI, and re-apply the settings (e.g. "text under icons", etc.)
	createGUI();
	applyMainWindowSettings( KGlobal::config(), autoSaveGroup() );
}

void KLettres::loadSettings()
{
	selectedLanguage = Prefs::languageNumber();
	//apply the font
	m_view->setFont(Prefs::font());
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
}

/** Hide and show the MenuBar */
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
	if (selectedLanguage == 0)//Czech
	{
		secondToolbar->insertButton ("C_caron.png", 10, SIGNAL( clicked() ), this, SLOT( slotPasteCcaron()), true, i18n("Try ") + QString::fromUtf8("Č", -1), 1 );
		secondToolbar->insertButton ("D_caron.png", 20, SIGNAL( clicked() ), this, SLOT( slotPasteDcaron()), true, i18n("Try ")+ QString::fromUtf8("Ď", -1), 2 );
		secondToolbar->insertButton ("R_caron.png", 30, SIGNAL( clicked() ), this, SLOT( slotPasteRcaron()), true, i18n("Try ") + QString::fromUtf8("Ř", -1), 3 );
		secondToolbar->insertButton ("S_caron.png", 40, SIGNAL( clicked() ), this, SLOT( slotPasteScaron()), true, i18n("Try ") + QString::fromUtf8("Š", -1), 4 );
		secondToolbar->insertButton ("T_caron.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteTcaron()), true, i18n("Try ")+ QString::fromUtf8("Ť", -1), 5);
		secondToolbar->insertButton ("Z_caron.png", 60, SIGNAL( clicked() ), this, SLOT( slotPasteZcaron()), true, i18n("Try ") + QString::fromUtf8("Ž", -1), 6 );
	}
	else if (selectedLanguage == 1)//Danish
	{
		secondToolbar->insertButton ("A_circle.png", 10, SIGNAL( clicked() ), this, SLOT( slotPasteAcircle()), true, i18n("Try ") + QString::fromUtf8("Å", -1), 1 );
		secondToolbar->insertButton ("A_withE.png", 20, SIGNAL( clicked() ), this, SLOT( slotPasteAwithE()), true, i18n("Try ") + QString::fromUtf8("Æ", -1), 2 );
		secondToolbar->insertButton ("O_barre.png", 30, SIGNAL( clicked() ), this, SLOT( slotPasteObarre()), true, i18n("Try ")+ QString::fromUtf8("Ø", -1), 3 );
	
	}
	else if (selectedLanguage == 2 || selectedLanguage==3)//Dutch and French
	{
		if (secondToolbar) secondToolbar->hide();
		setMinimumSize( QSize( 640, 480 ) );
		setMaximumSize( QSize( 640, 480 ) );
	}
	else if (selectedLanguage == 4)//Slovak
	{
		secondToolbar->insertButton ("A_acute.png", 10, SIGNAL( clicked() ), this, SLOT( slotPasteAacute()), true, i18n("Try ")+ QString::fromUtf8("Á", -1), 1 );
		secondToolbar->insertButton ("A_umlaut.png", 20, SIGNAL( clicked() ), this, SLOT( slotPasteAumlaut()), true, i18n("Try ")+ QString::fromUtf8("Ä", -1), 2 );
		secondToolbar->insertButton ("C_caron.png", 30, SIGNAL( clicked() ), this, SLOT( slotPasteCcaron()), true, i18n("Try ")+ QString::fromUtf8("Č", -1), 3 );
		secondToolbar->insertButton ("D_caron.png", 40, SIGNAL( clicked() ), this, SLOT( slotPasteDcaron()), true, i18n("Try ") + QString::fromUtf8("Ď", -1) , 4 );
		secondToolbar->insertButton ("E_acute.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteEacute()), true, i18n("Try ")+ QString::fromUtf8("É", -1) , 5 );
		secondToolbar->insertButton ("I_acute.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteIacute()), true, i18n("Try ") + QString::fromUtf8("Í", -1), 6 );
		secondToolbar->insertButton ("L_acute.png", 60, SIGNAL( clicked() ), this, SLOT( slotPasteLacute()), true, i18n("Try ") + QString::fromUtf8("Ĺ", -1), 7 );
		secondToolbar->insertButton ("L_apos.png", 70, SIGNAL( clicked() ), this, SLOT( slotPasteLapos()), true, i18n("Try ") + QString::fromUtf8("Ľ", -1), 8 );
		secondToolbar->insertButton ("N_caron.png", 40, SIGNAL( clicked() ), this, SLOT( slotPasteNcaron()), true, i18n("Try ") + QString::fromUtf8("Ň", -1), 9 );
		secondToolbar->insertButton ("O_acute.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteOacute()), true, i18n("Try ") + QString::fromUtf8("Ó", -1), 10 );
		secondToolbar->insertButton ("O_circ.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteOchap()), true, i18n("Try ") + QString::fromUtf8("Ô", -1), 11);
		secondToolbar->insertButton ("R_acute.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteRacute()), true, i18n("Try ")+ QString::fromUtf8("Ŕ", -1), 12 );
		secondToolbar->insertButton ("S_caron.png", 40, SIGNAL( clicked() ), this, SLOT( slotPasteScaron()), true, i18n("Try ")+ QString::fromUtf8("Š", -1), 13 );
		secondToolbar->insertButton ("T_caron.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteTcaron()), true, i18n("Try ") + QString::fromUtf8("Ť", -1), 14);
		secondToolbar->insertButton ("U_acute.png", 50, SIGNAL( clicked() ), this, SLOT( slotPasteUacute()), true, i18n("Try ")+ QString::fromUtf8("Ú", -1), 15 );
		secondToolbar->insertButton ("Z_caron.png", 60, SIGNAL( clicked() ), this, SLOT( slotPasteZcaron()), true, i18n("Try ")+ QString::fromUtf8("Ž", -1), 16 );
	}
	KConfig *config = kapp->config();
	config->setGroup("General Toolbar secondToolbar");
	if (config->readBoolEntry("Hidden"))
		secondToolbar->hide();
	else secondToolbar->show();
}

void KLettres::slotPasteCcaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Č", -1));//not setText() but append to existing string
}

void KLettres::slotPasteDcaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ď", -1));
}

void KLettres::slotPasteRcaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ř", -1));
}

void KLettres::slotPasteScaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Š", -1));
}

void KLettres::slotPasteTcaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ť", -1));
}

void KLettres::slotPasteZcaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ž", -1));
}

void KLettres::slotPasteAcircle()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Å", -1));
}
void KLettres::slotPasteAwithE()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Æ", -1));
}
void KLettres::slotPasteObarre()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ø", -1));
}

void KLettres::slotPasteAacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Á", -1));
}

void KLettres::slotPasteAumlaut()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ä", -1));
}

void KLettres::slotPasteEacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("É", -1));
}

void KLettres::slotPasteIacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Í", -1));
}

void KLettres::slotPasteLacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ĺ", -1));
}

void KLettres::slotPasteLapos()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ľ", -1));
}

void KLettres::slotPasteNcaron()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ň", -1));
}

void KLettres::slotPasteOacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ó", -1));
}

void KLettres::slotPasteOchap()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ô", -1));
}

void KLettres::slotPasteRacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ŕ", -1));
}

void KLettres::slotPasteUacute()
{
	m_view->line1->setText(m_view->line1->text()+QString::fromUtf8("Ú", -1));
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

#include "klettres.moc"
