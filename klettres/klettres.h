/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>

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
   ///Holds the non i18n language, style is the background mode, either kid or grownup
   QString langString, style;
   //Holds the file from which the letters or syllables are read
   int length, input, num, numRead;
   ///is false when menubar button is not shown
   bool menuBool;
   ///is false when kid button not shown
   bool kidBool;
   ///is false when grownup button not shown
   bool grownBool;

   void registerLanguage(const QString &menuItem, const char *actionId, bool enabled);
   /**
    *Switch to another language
    *@param - uint is the id of the new language
    */
   void changeLanguage(uint newLanguage);
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

protected:
    /**
     * This function is called when it is time for the app to save its
     * properties for session management purposes.
     */
    void saveProperties(KConfig *);

    /**
     * This function is called when this app is restored.  The KConfig
     * object points to the session management config file that was saved
     * with @ref saveProperties
     */
    void readProperties(KConfig *);


private slots:

    /// Configure shortcut keys
    void optionsConfigureKeys();
    ///Configure toolbars icons, use the standard toollbar editor
    void optionsConfigureToolbars();
     ///Open the Settings->Configure KLettres dialog
    void optionsPreferences();
    /**This slot is called when user clicks "Ok" or "Apply" in the toolbar editor.
     * Recreate our GUI, and re-apply the settings (e.g. "text under icons", etc.)
     */
    void newToolbarConfig();
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
       /**Read settings from KLettres config file
    *If no config file found, put French as default
    */
    void loadSettings();
    ///Switch to language #0 Czech
    void language0();
    ///Switch to language #1 danish
    void language1();
    ///Switch to language #2 French
    void language2();
    ///Switch to language #3 Dutch
    void language3();
    ///Switch to language #4 Slovak
    void language4();

    void slotPasteCcaron();
    void slotPasteDcaron();
    void slotPasteRcaron();
    void slotPasteScaron();
    void slotPasteTcaron();
    void slotPasteZcaron();
    void slotPasteAcircle();
    void slotPasteAwithE();
    void slotPasteObarre();
    void slotPasteAacute();
    void slotPasteAumlaut();
    void slotPasteEacute();
    void slotPasteIacute();
    void slotPasteLacute();
    void slotPasteLapos();
    void slotPasteOacute();
    void slotPasteOchap();
    void slotPasteRacute();
    void slotPasteUacute();
    void slotPasteNcaron();

private:
    ///Enable accel keys
    void setupAccel();
    ///Setup our actins using klettresui.rc
    void setupActions();
    /**
     * Set the label in the StatusBar to indicate the correct language
     * @param int - The id of the new language
     */
    void updateLanguage(int );
    /**
     *see what languages data are present in the user machine
     *see what language is used for KDE
     *set the default language to that language if possible, to fr otherwise
     */
    void loadLanguages();
    ///Set the correct buttons on the second toolbar according to the language
    void loadLangToolBar();

private:

    ///Action that enables the ShowMenuBar item in the Settings menu
    KToggleAction *m_action;
    ///Action that sets up the Language menu
    KSelectAction *language_menu;
    ///Action that calls the Font Chooser Dialog
    KAction *fontAct;
    ///Number corresponding to the selected language: 0 is Czech, 1 is Danish, 2 is French (default), 3 is Dutch, 4 is Slovak
    uint selectedLanguage;
    ///Total number of languages
    uint languages;
    ///Name of actions for registered languages
    QString languageActions[16];
    ///Language codes of available languages
    QStringList m_languages;
    ///the language used in KDE for the user
    QString userLanguage;
    ///the language that is set to default: either userLanguage or en if userLanguage is not available
    int defaultLang;
    ///second toolbar with buttons of special characters per language
    KToolBar *secondToolbar;
};

#endif // _KLETTRES_H_
