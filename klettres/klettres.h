/*
 * Copyright (C) 2001-2004 Anne-Marie Mahfouf <annma@kde.org>

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

#ifndef _KLETTRES_H_
#define _KLETTRES_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

//KDE headers
#include <kmainwindow.h>
#include "klettresview.h"
#include "soundfactory.h"

class KToggleAction;
class KSelectAction;
class KToolBar;
class KComboBox;
class QDomDocument;
class KLNewStuff;

/**
 * This class serves as the main window for KLettres.  It handles the
 * menus, toolbars, and status bars.
 *
 * @short Main window class
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 1.1
 */
class KLettres : public KMainWindow
{
    Q_OBJECT
public:

	///Constructor
	KLettres();
	///Destructor
	virtual ~KLettres();
	///Label on statusBar that displays the current language
	QLabel *langLabel;
	///Label on the statusBar that displays the current level
	QLabel *levLabel;
	///Holds the current font
	QFont newFont;
	///Create an instance of a KToolBar
	KToolBar *tb;
	///Combobox that holds the different levels in the toolbar
	KComboBox *lev_comb;
	///Holds the i18n current language
	QString language;
	///Holds the file from which the letters or syllables are read
	int length, input, num, numRead;
	///is false when menubar button is not shown
	bool menuBool;
	///is false when kid button not shown
	bool kidBool;
	///is false when grownup button not shown
	bool grownBool;
	///Register an available language
	void registerLanguage(const QString &language, const QString &menuItem);
	/**
	*Load the xml file
	*@param - the xml file
	*@return - bool true if the xml document is found and well formed, false otherwise
	*/
	bool loadLayout(QDomDocument &layoutDocument);
	///Call an instance of the KLettresView widget
	KLettresView *m_view;
	///Sound class
	SoundFactory *soundFactory;
	///All available language codes
	QStringList m_languages;
	///All the special characters from a language file, these characters will be as buttons on the Special Characters Toolbar
	QStringList allData;
	///All available language names
	QStringList m_languageNames;
	///Number corresponding to the selected language: 0 is Czech, 1 is Danish, 2 is French (default), 3 is Dutch, 4 is Slovak
	uint selectedLanguage;
	///Action that sets up the Language menu
	KSelectAction *m_languageAction;

private slots:

	///Open the Settings->Configure KLettres dialog
	void optionsPreferences();
	///Hide and show the MenuBar, called by Settings->Show Menubar
	void slotMenubar();
	///Show menuBar, called by the MenuBar button which is only visible when the menubar is not shown
	void slotShowM();
	///Switch to the grown-up look, menubar is shown
	void slotGrownup();
	///Switch to the kid look, menubar is hidden
	void slotKid();
	/**
	 *When the user change levels
	 *@param int - The id of the new level
	 */
	void slotChangeLevel(int );
	/**
	 *Update the level menu and level combobox
	 * @param int - The id of the new level
	 */
	void updateLevMenu(int );
	/**
	 *Switch to another language
	 *@param - newLanguage the index of the new language in m_languages
	 */
	void changeLanguage(int newLanguage);
	/**Read settings from KLettres config file
	 *If no config file found, put French as default
	 */
	void loadSettings();
	///When a button is clicked on the characters toolbar, the corresponding character is written in the lineedit 
	void slotPasteChar();
	///Access the KNewStuff class to install new data
	void downloadNewStuff();
	///Call the timer settings dialog
	void slotTimer();

private:
	///Enable accel keys
	void setupAccel();
	///Setup our actins using klettresui.rc
	void setupActions();
	/**
	 * Set the label in the StatusBar to indicate the correct language
	 */
	void updateLanguage();
	///Set the correct buttons on the second toolbar according to the language
	void loadLangToolBar();
    


private:

	///Action that enables the ShowMenuBar item in the Settings menu
	KToggleAction *m_action;
	///Action that calls the Font Chooser Dialog
	KAction *fontAct;
	
	KAction *timerAct;
	///Second toolbar with buttons of special characters per language
	KToolBar *secondToolbar;
	///Create a KNewStuff instance
	KLNewStuff *mNewStuff;
	/**generates icons for the special characters toolbar
     	 * @param c the character that will be painted on the icon
         */
	QString charIcon(const QChar &);
};

#endif // _KLETTRES_H_
