/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */


//KDE headers
#include <kapplication.h>
#include <kconfig.h>
#include <kdebug.h>
#include <kfontdialog.h>
#include <kglobalsettings.h>
#include <kiconloader.h>
#include <klocale.h>
//Qt headers
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qradiobutton.h>
//Project headers
#include "pref.h"


KLettresPreferences::KLettresPreferences()
    : KDialogBase(IconList, i18n("KLettres Preferences"),
                  Help|Default|Ok|Apply|Cancel, Ok)
{
    //read the config file to set everything accordingly
    readConfig();
    //GUI
    QFrame *frame;
    frame = addPage(i18n("General"), i18n("General"), BarIcon("gear", KIcon::SizeMedium));
    m_pageOne = new KLettresPrefPageOne(frame);
    connect(m_pageOne->levelBox, SIGNAL(activated(int)), this, SLOT(slotChangeLevel(int)));
    connect(m_pageOne->levelBox, SIGNAL(activated(int)), this, SLOT(slotChanged()));

    QObject::connect(m_pageOne->lookGroup, SIGNAL(clicked(int)), this, SLOT(slotChangeLook(int)));
    QObject::connect(m_pageOne->lookGroup, SIGNAL(clicked(int)), this, SLOT(slotChanged()));

    frame = addPage(i18n("Fonts"), i18n("Font settings"), BarIcon ("fonts", KIcon::SizeMedium));
    m_pageTwo = new KLettresPrefPageTwo(frame);

    connect (m_pageTwo->fdlg, SIGNAL (fontSelected( const QFont & )), this, SLOT (slotSetNewFont( const QFont & )));

    frame = addPage(i18n("Language"), i18n("Sounds & Letters Language"), BarIcon ("locale", KIcon::SizeMedium));
    m_pageThree = new KLettresPrefPageThree(frame);

    QObject::connect(m_pageThree->langGroup, SIGNAL(clicked(int)), this, SLOT(slotLang(int)));
    QObject::connect(m_pageThree->langGroup, SIGNAL(clicked(int)), this, SLOT(slotChanged()));

    //set everything according to config file
    slotSet();
    //disable the Apply button before any changes are made
    enableButton( Apply, false);
}

KLettresPrefPageOne::KLettresPrefPageOne(QWidget *parent)
    : pref1ui(parent)
{
	adjustSize();
}

KLettresPrefPageTwo::KLettresPrefPageTwo(QWidget *parent)
    : QFrame(parent)
{
 QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAutoAdd(true);

    fdlg = new KFontChooser(this);
    adjustSize();
 }

 KLettresPrefPageThree::KLettresPrefPageThree(QWidget *parent)
    : pref2ui(parent)
{
	adjustSize();
}

void KLettresPreferences::readConfig()
{
   	KConfigBase *conf = kapp->config();
	if (conf)
	{
    		conf->setGroup("Language");
    		langString=conf->readEntry("MyLanguage");
		//read style and set default
    		style=conf->readEntry("myStyle");
		if (conf->hasKey("myStyle") == false)
			style = "grownup";
		//read level and set default
    		niveau=conf->readNumEntry("myLevel");
    		if (conf->hasKey("myLevel") == false)
			niveau = 1;
		//read font and set default
    		conf->setGroup("Font");
    		newFont=QFont(conf->readEntry("Family"), conf->readNumEntry("Size"), conf->readNumEntry("Weight"), false);
		if (conf->hasKey("Family") == false)
		{
			newFont = QFont(KGlobalSettings::largeFont());
    			newFont.setBold(true);
		}
	}
}

//Set the system defaults
void KLettresPreferences::slotDefault()
{
    niveau = 1;
    style = "grownup";
    langString = "French";
    newFont = QFont(KGlobalSettings::largeFont());
    newFont.setBold(true);
    slotSet();
    slotChanged();
}

//Apply changes made in the dialog and close the dialog
void KLettresPreferences::slotOk()
{
	if( configChanged )
     	   slotApply();
	accept();
}

//Apply changes made in the dialog and leave the dialog close
void KLettresPreferences::slotApply()
{
	enableButton( Apply, false );
        configChanged = false;
	writeConfig();
	emit aClicked();
}

//Don't validate the changes in the dialog and close the dialog
void KLettresPreferences::slotCancel()
{
	accept();
}

void KLettresPreferences::slotSet()
{
    //first page
    m_pageOne->levelBox->setCurrentItem(niveau-1);
    if (style == "grownup")
    	m_pageOne->grownupButton->setChecked(true);
    if (style == "kid")
    	m_pageOne->kidButton->setChecked(true);
    //second page
    m_pageTwo->newFont = newFont;
    m_pageTwo->fdlg->setFont(newFont);
    //third page
    if (langString == "Danish")
    	m_pageThree->daBox->setChecked(true);
    if (langString == "Dutch")
    	m_pageThree->duBox->setChecked(true);
    if (langString == "French")
    	m_pageThree->frBox->setChecked(true);
 }

//Write settings in config
void KLettresPreferences::writeConfig()
{
	KConfigBase *conf = kapp->config();
	if (conf)
	{
		conf->setGroup("Language");
		conf->writeEntry("MyLanguage", langString);
    		conf->writeEntry("myLevel", niveau);
		conf->writeEntry("myStyle", style);
		conf->setGroup("Font");
    		conf->writeEntry("Family", newFont.family());
    		conf->writeEntry("Size", newFont.pointSize());
    		conf->writeEntry("Weight", newFont.weight());
		conf->sync();
	}
}

//change Font, pass it to the main window and save it in config
void KLettresPreferences::slotSetNewFont(const QFont &font)
{
	if (font.family() != newFont.family() ||  newFont.pointSize() != font.pointSize() || newFont.weight() != font.weight())
	{
		slotChanged();
		newFont = font;
	}
}

//called whenever a change has been made in the settings
//Apply button is enabled so it can be clicked to apply the changes
void KLettresPreferences::slotChanged()
{
    enableButton( Apply, true );
    configChanged = true;
}

void KLettresPreferences::slotChangeLevel(int id)
{
	m_pageOne->levelBox->setCurrentItem(id);
	niveau = id+1;
	enableButton( Apply, false );
        configChanged = false;
}

void KLettresPreferences::slotChangeLook(int id)
{
    switch (id) {
        case 0:
            style = "grownup";
            break;
	case 1:
            style = "kid";
            break;
    }
    	writeConfig();
	enableButton( Apply, false );
        configChanged = false;
}

void KLettresPreferences::slotLang(int id)
{
	switch (id) {
		case 0:
			langString = "Danish";
			break;
		case 1:
			langString = "Dutch";
			break;
		case 2:
			langString = "French";
			break;
	}
	slotSet();
	enableButton( Apply, false );
        configChanged = false;
}

#include "pref.moc"
