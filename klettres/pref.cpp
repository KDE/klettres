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
#include <qlayout.h>
//Project headers
#include "pref.h"


KLettresPreferences::KLettresPreferences()
    : KDialogBase(IconList, i18n("Preferences"),
                  Help|Default|Ok|Apply|Cancel, Ok)
{
    //GUI
    QFrame *frame;

    frame = addPage(i18n("Fonts"), i18n("Font settings"), BarIcon ("fonts", KIcon::SizeMedium));
    m_pageOne = new KLettresPrefPageOne(frame);

    connect (m_pageOne->fdlg, SIGNAL (fontSelected( const QFont & )), this, SLOT (slotSetNewFont( const QFont & )));

    loadSettings();
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


void KLettresPreferences::loadSettings()
{
   	KConfigBase *conf = kapp->config();
	if (conf)
	{
		//read font and set default
    		conf->setGroup("Font");
    		newFont=QFont(conf->readEntry("Family"), conf->readNumEntry("Size"), conf->readNumEntry("Weight"), false);
		if (conf->hasKey("Family") == false)
		{
			newFont = QFont(KGlobalSettings::largeFont());
    			newFont.setBold(true);
		}
	}
        m_pageOne->newFont = newFont;
    	m_pageOne->fdlg->setFont(newFont);
}

//Set the system defaults
void KLettresPreferences::slotDefault()
{
    newFont = QFont(KGlobalSettings::largeFont());
    newFont.setBold(true);
    m_pageOne->newFont = newFont;
    m_pageOne->fdlg->setFont(newFont);
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
        KConfigBase *config = kapp->config();
        config->setGroup("Font");
        config->writeEntry("Family", newFont.family());
        config->writeEntry("Size", newFont.pointSize());
        config->writeEntry("Weight", newFont.weight());
	 emit aClicked();
}

//Don't validate the changes in the dialog and close the dialog
void KLettresPreferences::slotCancel()
{
	accept();
}

//change Font, pass it to the main window if Apply is clicked
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

#include "pref.moc"