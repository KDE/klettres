/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#include <qtooltip.h>
//KDE headers
#include <kcombobox.h>
#include <klocale.h>
#include <kdebug.h>
#include <kmenubar.h>
#include <kmessagebox.h>
#include <kstatusbar.h>
#include <kkeydialog.h>
#include <kfiledialog.h>
#include <kedittoolbar.h>
#include <kaction.h>
#include <kfontdialog.h>
//Project headers
#include "klettres.h"
#include "pref.h"
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
    languages = 0;
    // tell the KMainWindow that this is indeed the main widget
    setCentralWidget(m_view);
    //Read config
    loadSettings();
    //selectedLanguage must be read from config file
    soundFactory = new SoundFactory(this, "sounds", selectedLanguage);
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
    tb->insertSeparator(5, 5);

    //Set up StatusBar
    KStatusBar *st=statusBar();
    langLabel = new QLabel(st);
    levLabel = new QLabel(st);
    st->addWidget(levLabel);
    st->insertFixedItem("", 1);//add a space
    st->addWidget(langLabel);
    statusBar()->show();

    slotSetFont();//set the font from config
    //from the Read config, growup is set as default if no style
    if (style=="grownup") slotGrownup();
	else slotKid();

    if (!m_view->niveau) m_view->niveau = 1;

    updateLevMenu(m_view->niveau-1);

    m_view->selectedLanguage = selectedLanguage;
    updateLanguage(selectedLanguage);

    m_view->game();
}

KLettres::~KLettres()
{
}

void KLettres::setupActions()
{
    KStdAction::quit(kapp, SLOT(quit()), actionCollection());

    m_action = new KToggleAction(i18n("Show &Menubar"),CTRL+Key_M, this, SLOT(slotMenubar()), actionCollection(), "menubar");
    m_action->setChecked(true);

    createStandardStatusBarAction();
    setStandardToolBarMenuEnabled(true);

    KStdAction::keyBindings(this, SLOT(optionsConfigureKeys()), actionCollection());
    KStdAction::configureToolbars(this, SLOT(optionsConfigureToolbars()), actionCollection());
    fontAct = new KAction(i18n("Change &Font"), "fonts", CTRL+Key_F, this, SLOT(optionsPreferences()), actionCollection(), "font");

    createGUI();
}

// Register an available language
void KLettres::registerLanguage(const QString &menuItem, const char *actionId, bool enabled)
{
  KToggleAction *t = 0;

  switch (languages)
  {
  	case 0: t = new KToggleAction(i18n(menuItem.latin1()), 0, this, SLOT(language0()), actionCollection(), actionId);
		break;
  	case 1: t = new KToggleAction(i18n(menuItem.latin1()), 0, this, SLOT(language1()), actionCollection(), actionId);
		break;
  	case 2: t = new KToggleAction(i18n(menuItem.latin1()), 0, this, SLOT(language2()), actionCollection(), actionId);
		break;
  	case 3: t = new KToggleAction(i18n(menuItem.latin1()), 0, this, SLOT(language3()), actionCollection(), actionId);
		break;
  }

  if( t ) {
      if (languages == selectedLanguage) t->setChecked(true);
      t->setEnabled(enabled);
      languageActions[languages] = actionId;
      languages++;
  }
}

void KLettres::changeLanguage(uint newLanguage)
{
  // Do not accept to switch to same language
  if (newLanguage == selectedLanguage) {
    // newLanguage should stay checked
    ((KToggleAction*) actionCollection()->action(languageActions[newLanguage].latin1()))->setChecked(true);
    return;
  }
  // Unselect preceeding language
  ((KToggleAction*) actionCollection()->action(languageActions[selectedLanguage].latin1()))->setChecked(false);
  ((KToggleAction*) actionCollection()->action(languageActions[newLanguage].latin1()))->setChecked(true);
  // Change language in the remembered options
  selectedLanguage = newLanguage;
  // write new language in config file
  KConfig *config = kapp->config();
  if (config)
  {
    config->setGroup("General");
    config->writeEntry("LanguageNumber", selectedLanguage);
  }
  // Update the StatusBar
  updateLanguage(selectedLanguage);
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
     QString mString=i18n("The sounds.xml file was not found in\n"
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

///Switch to language #0
void KLettres::language0()
{
  changeLanguage(0);
}

///Switch to language #1
void KLettres::language1()
{
  changeLanguage(1);
}

///Switch to language #2
void KLettres::language2()
{
  changeLanguage(2);
}

///Switch to language #3
void KLettres::language3()
{
  changeLanguage(3);
}

///Set the label in the StatusBar to indicate the correct language
void KLettres::updateLanguage(int index)
{
    switch(index){
	case 0:
            langString = i18n("Czech");
            break;
        case 1:
            langString = i18n("Danish");
            break;
        case 2:
            langString = i18n("French");
            break;
        case 3:
            langString = i18n("Dutch");
            break;
    }
    langLabel->setText(i18n("Current language is %1").arg(langString));
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
    KConfig *config = kapp->config();
    QString option;
    config->setGroup("General");
    //if no language, default language is french
    option = config->readEntry("LanguageNumber", "2");
    selectedLanguage = option.toInt();
    if (selectedLanguage <= 0) selectedLanguage = 0;
    if (selectedLanguage > 3) selectedLanguage = 3;
    //if no style, default style is grownup
    style=config->readEntry("myStyle", "grownup");
    //if no level, default level is 1
    m_view->niveau=config->readNumEntry("myLevel", 1);
    config->setGroup("Font");
    newFont=QFont(config->readEntry("Family", "Charter"), config->readNumEntry("Size",48), config->readNumEntry("Weight",75), false);
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
    KConfig *config = kapp->config();
    config->setGroup("General");
    config->writeEntry("myStyle", m_view->style);
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
    KConfig *config = kapp->config();
    config->setGroup("General");
    config->writeEntry("myStyle", m_view->style);
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
    //Change level effectively by reloading sounds
    soundFactory->change(selectedLanguage);
    //write new level in config file
    KConfig *config = kapp->config();
    config->setGroup("General");
    config->writeEntry("myLevel", m_view->niveau);
    //update game effectively
    m_view->game();
}

void KLettres::updateLevMenu(int id)
{
    lev_comb->setCurrentItem(id);
    levLabel->setText(i18n("Current level is %1").arg(m_view->niveau));
}

///Set new font after a change in the Configure KLettres dialog
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
