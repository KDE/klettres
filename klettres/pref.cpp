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
    loadSettings();
    //GUI
    QFrame *frame;

    frame = addPage(i18n("Fonts"), i18n("Font settings"), BarIcon ("fonts", KIcon::SizeMedium));
    m_pageOne = new KLettresPrefPageOne(frame);

    connect (m_pageOne->fdlg, SIGNAL (fontSelected( const QFont & )), this, SLOT (slotSetNewFont( const QFont & )));

    frame = addPage(i18n("Language"), i18n("Sounds & Letters Language"), BarIcon ("locale", KIcon::SizeMedium));
    m_pageTwo = new KLettresPrefPageTwo(frame);

    QObject::connect(m_pageTwo->langGroup, SIGNAL(clicked(int)), this, SLOT(slotLang(int)));
    QObject::connect(m_pageTwo->langGroup, SIGNAL(clicked(int)), this, SLOT(slotChanged()));

    //set everything according to config file
    slotSet();
    //disable the Apply button before any changes are made
    enableButton( Apply, false);
}


KLettresPrefPageOne::KLettresPrefPageOne(QWidget *parent)
    : QFrame(parent)
{
 QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setAutoAdd(true);

    fdlg = new KFontChooser(this);
    adjustSize();
 }

 KLettresPrefPageTwo::KLettresPrefPageTwo(QWidget *parent)
    : pref2ui(parent)
{
	adjustSize();
}

void KLettresPreferences::loadSettings()
{
   	KConfigBase *conf = kapp->config();
	if (conf)
	{
    		conf->setGroup("General");
    		langString=conf->readEntry("MyLanguage");

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
	emit aClicked();
}

//Don't validate the changes in the dialog and close the dialog
void KLettresPreferences::slotCancel()
{
	accept();
}

void KLettresPreferences::slotSet()
{
    //font page
    m_pageOne->newFont = newFont;
    m_pageOne->fdlg->setFont(newFont);
    //third page
    if (langString == "Danish")
    	m_pageTwo->daBox->setChecked(true);
    if (langString == "Dutch")
    	m_pageTwo->duBox->setChecked(true);
    if (langString == "French")
    	m_pageTwo->frBox->setChecked(true);
 }

//change Font, pass it to the main window and save it in config
void KLettresPreferences::slotSetNewFont(const QFont &font)
{
	if (font.family() != newFont.family() ||  newFont.pointSize() != font.pointSize() || newFont.weight() != font.weight())
	{
		slotChanged();
		newFont = font;
	}
	//write new font in config
	KConfigBase *conf = kapp->config();
	if (conf)
	{
		conf->setGroup("Font");
    		conf->writeEntry("Family", newFont.family());
    		conf->writeEntry("Size", newFont.pointSize());
    		conf->writeEntry("Weight", newFont.weight());
		conf->sync();
	}
}

//called whenever a change has been made in the settings
//Apply button is enabled so it can be clicked to apply the changes
void KLettresPreferences::slotChanged()
{
    enableButton( Apply, true );
    configChanged = true;
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
	//write new language in config
	KConfigBase *conf = kapp->config();
	if (conf)
	{
		conf->setGroup("General");
		conf->writeEntry("MyLanguage", langString);
		conf->sync();
	}
}

#include "pref.moc"
