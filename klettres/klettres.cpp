/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#include <qtooltip.h>
//KDE headers
#include <kcombobox.h>
#include <ktoolbar.h>
#include <kconfig.h>
#include <kglobal.h>
#include <klocale.h>
#include <kdebug.h>
#include <kiconloader.h>
#include <kmenubar.h>
#include <kstatusbar.h>
#include <kkeydialog.h>
#include <kaccel.h>
#include <kfiledialog.h>
#include <kedittoolbar.h>
#include <kstdaccel.h>
#include <kaction.h>
#include <kstdaction.h>
#include <kfontdialog.h>
#include <kglobalsettings.h>
//Project headers
#include "klettres.h"
#include "pref.h"

const int ID_KIDB      = 100;
const int ID_GROWNB    = 101;
const int ID_MENUBARB  = 102;

KLettres::KLettres()
    : KMainWindow( 0, "KLettres" ),
      m_view(new KLettresView(this))
{

    // tell the KMainWindow that this is indeed the main widget
    setCentralWidget(m_view);

    // then, setup our actions
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
    tb->insertSeparator(5, 5);
    //Language combobox
    lang_comb= new KComboBox(tb);
    lang_comb->insertItem( i18n( "Danish" ) );
    lang_comb->insertItem( i18n( "Dutch" ) );
    lang_comb->insertItem( i18n( "French" ) );
    tb->insertWidget(6, 100, lang_comb, 6); //id, width, widget,
    connect(lang_comb, SIGNAL(activated(int)), this, SLOT(changeNumeration(int)));
    QToolTip::add(lang_comb, i18n("Change the language to learn"));
    tb->insertSeparator(7, 7);

    //Set up StatusBar
    KStatusBar *st=statusBar();
    langLabel = new QLabel(st);
    levLabel = new QLabel(st);
    st->addWidget(levLabel);
    st->insertFixedItem("", 1);//add a space
    st->addWidget(langLabel);
    statusBar()->show();

    //Load settings from config file
    //if not, put default as French
    loadSettings();
    slotSetFont();//set the font from config
    if (!langString) //if there is no config file
    {
	QString mString=i18n("This is the first time you have run KLettres.\n"
                             "The default learning language is set to French.\n"
			     "You can change the language in the Settings -> Learning Language menu.\n\n"
			      "Default level is Level 1, the easiest one.\n"
			      "You can change the level in the Settings -> Levels menu.");
	KMessageBox::information( this, mString,"KLettres - Default" );
	m_view->l1=26;   //set French as default language
	m_view->l2=28;
	langString="French";
	language=i18n("%1").arg(langString);
	m_view->niveau=1;
	slotGrownup();//default style==grown-up
    }
    else
    {
	if (style=="grownup") slotGrownup();
	else slotKid();
    }
    if (!m_view->niveau) m_view->niveau = 1;
    setLang();
    updateLevMenu(m_view->niveau-1);
}

KLettres::~KLettres()
{
}

void KLettres::setupActions()
{
    KStdAction::quit(this, SLOT(slotQuit()), actionCollection());

    m_action = new KToggleAction(i18n("Show &Menubar"),CTRL+Key_M, this, SLOT(slotMenubar()), actionCollection(), "menubar");
    m_action->setChecked(true);

    createStandardStatusBarAction();
    setStandardToolBarMenuEnabled(true);

    KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
    KStdAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
    KStdAction::preferences(this, SLOT(optionsPreferences()), actionCollection());

    //Settings->Choose Language menu
    QStringList language_list;
    language_list.append(i18n("D&anish"));
    language_list.append(i18n("&Dutch"));
    language_list.append(i18n("F&rench"));
    language_menu = new KSelectAction(i18n("Learning L&anguage"), 0, actionCollection(), "languages");
    language_menu->setItems(language_list);
    connect(language_menu, SIGNAL(activated(int)), this, SLOT(changeNumeration(int)));
    connect(language_menu, SIGNAL(activated(int)), this, SLOT(updateLangMenu(int)));

    createGUI();
}

void KLettres::saveProperties(KConfig *)
{
    // the 'config' object points to the session managed
    // config file.  anything you write here will be available
    // later when this app is restored
}

void KLettres::readProperties(KConfig *)
{
    // the 'config' object points to the session managed
    // config file.  this function is automatically called whenever
    // the app is being restored.  read in here whatever you wrote
    // in 'saveProperties'
}

void KLettres::optionsConfigureKeys()
{
    KKeyDialog::configureKeys(actionCollection(), "klettresui.rc");
}

void KLettres::optionsConfigureToolbars()
{
    // use the standard toolbar editor
    saveMainWindowSettings( KGlobal::config(), autoSaveGroup() );
    KEditToolbar dlg(actionCollection());
    connect(&dlg, SIGNAL(newToolbarConfig()), this, SLOT(newToolbarConfig()));
    dlg.exec();
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
    KConfig *config = kapp->config();
    config->setGroup("General");
    langString=config->readEntry("MyLanguage");
    style=config->readEntry("myStyle");
    m_view->niveau=config->readNumEntry("myLevel");
    config->setGroup(langString);
    m_view->l1 =config->readNumEntry("Alphabet");
    m_view->l2 =config->readNumEntry("Syllables");
    config->setGroup("Font");
    newFont=QFont(config->readEntry("Family"), config->readNumEntry("Size"), config->readNumEntry("Weight"), false);
}

void KLettres::writeConfig()
{
    //write current config
    KConfig *config = kapp->config();
    config->setGroup("General");
    config->writeEntry("MyLanguage", langString);
    config->writeEntry("myStyle", m_view->style);
    config->writeEntry("myLevel", m_view->niveau);
    config->setGroup("French");
    config->writeEntry("Alphabet", 26);
    config->writeEntry("Syllables", 28);
    config->setGroup("Dutch");
    config->writeEntry("Alphabet", 22);
    config->writeEntry("Syllables", 26);
    config->setGroup("Danish");
    config->writeEntry("Alphabet", 29);
    config->writeEntry("Syllables", 28);
    config->setGroup("Font");
    config->writeEntry("Family", newFont.family());
    config->writeEntry("Size", newFont.pointSize());
    config->writeEntry("Weight", newFont.weight());
}

void KLettres::optionsPreferences()
{
    KLettresPreferences dlg;
    dlg.resize(530, 450);
    dlg.configChanged = false;
    QObject::connect(&dlg, SIGNAL(aClicked()), this, SLOT(slotClickApply()));
    if (dlg.exec())
    {
        // redo your settings
    }
}

//when Apply button in Preferences dialog is clicked, refresh view
void KLettres::slotClickApply()
{
     KLettresPreferences dlg;
     //refresh the font when changed in pref dialog
      if (newFont.family() != dlg.newFont.family() ||  newFont.pointSize() != dlg.newFont.pointSize() || newFont.weight() != dlg.newFont.weight())
      {
	newFont = dlg.newFont;
	slotSetFont();
      }
     //refresh the language if changed
      if (langString!=dlg.langString)
      {
      	  langString = dlg.langString;
	  setLang();
      }

}

void KLettres::slotQuit()
{
      writeConfig();
      kapp->quit();
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
    style = m_view->style;
    writeConfig();
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
    style = m_view->style;
    writeConfig();
}

void KLettres::changeNumeration(int id)
{
    updateLangMenu(id);
    switch (id) {
        case 0:
            langString="Danish";
            break;
        case 1:
            langString="Dutch";
            break;
	case 2:
            langString="French";
            break;
    }
    language=i18n(langString.latin1());
    writeConfig();
    loadSettings();
    langLabel->setText(i18n("Current language is %1").arg(language));
    language_menu->setCurrentItem(id);
    lang_comb->setCurrentItem(id);
    m_view->langLoc=langString;
    m_view->game();
}

void KLettres::updateLangMenu(int id)
{
    language_menu->setCurrentItem(id);
    lang_comb->setCurrentItem(id);
}

void KLettres::setLang()
{
    int id=2;
    if (langString=="Danish")//not i18n because in config
    	id=0;
    if (langString=="Dutch")//not i18n because in config
	id=1;
    if (langString=="French")//not i18n because in config
	id=2;

    changeNumeration(id);
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
    m_view->niveau=id+1;
    updateLevMenu(id);
    writeConfig();
    m_view->game();
}

void KLettres::updateLevMenu(int id)
{
    lev_comb->setCurrentItem(id);
    levLabel->setText(i18n("Current level is %1").arg(m_view->niveau));
}

void KLettres::slotSetFont()
{
     if (newFont.pointSize()==1)
    {
    	newFont=QFont(KGlobalSettings::largeFont());
    	newFont.setBold(true);
    }
    //otherwise newFont=read from config
    m_view->button1->setFont(newFont);
    m_view->line1->setFont(newFont);
}

#include "klettres.moc"
