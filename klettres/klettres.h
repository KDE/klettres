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


#ifndef KLETTRES_H
#define KLETTRES_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <kmainwindow.h>

#include "klettresview.h"
#include "soundfactory.h"

class QLabel;
class KToggleAction;
class KSelectAction;
class KComboBox;
class KToolBar;
class KLNewStuff;

/**
 * @short Application Main Window
 * @author Anne-Marie Mahfouf <annemarie.mahfouf@free.fr>
 * @version 1.4
 */
class KLettres : public KMainWindow
{
    Q_OBJECT
public:

    ///Constructor
    KLettres();
    ///Destructor
    virtual ~KLettres();

    ///Sound class
    SoundFactory *soundFactory;
    ///All available language codes
    QStringList m_languages;
    ///All available language names
    QStringList m_languageNames;
    /**
    *Load the xml file
    *@param layoutDocument the xml file
    *@return bool true if the xml document is found and well formed, false otherwise
    */
    bool loadLayout(QDomDocument &layoutDocument);
    ///Number corresponding to the selected language: 0 is Czech, 1 is Danish, 2 is English (default), 3 is French, 4 is Dutch, 5 is Slovak
    //uint selectedLanguage;
    ///Action that sets up the Language menu
    KSelectAction *m_languageAction;
    ///Look for all languages available
    void findLanguages();

    public slots:
    ///Set the new language
    void slotChangeLanguage(int);

protected:
    ///Call an instance of the KLettresView widget
    KLettresView *m_view;
    ///Action that enables the ShowMenuBar item in the Settings menu
    KToggleAction *m_menubarAction;
    ///Action that sets up the Level menu
    KSelectAction *m_levelAction;
    ///Action that sets up the Look menu
    KSelectAction *m_themeAction;
    ///Action allow the Kid mode
    KToggleAction *m_kidAction;
    ///Action allow the Grownup mode
    KToggleAction *m_grownupAction;
    ///Label stating the language in the statusbar
    QLabel *m_langLabel;
    ///Label stating the level in the statusbar
    QLabel *m_levLabel;
    ///Holds the levels
    QStringList m_levelsNames;
    ///Holds the looks
    QStringList m_themesNames;
    ///Create an instance of a KToolBar
    KToolBar *m_mainToolbar;
    ///Second toolbar with buttons of special characters per language
    KToolBar *m_secondToolbar;
    ///is false when menubar button is not shown
    bool menuBool;
    ///Build the main window menus
    void setupActions();
    ///Create and setup statusbar
    void setupStatusbar();
    ///Create main and second toolbars
    void setupToolbars();
    /**generates icons for the special characters toolbar
     * @param c the character that will be painted on the icon
     */
    QString charIcon(const QChar &c);
    /**
     *Update the level menu and level combobox
     * @param id The id of the new level
     */
    void updateLevMenu(int id);
    ///Create a KNewStuff instance
    KLNewStuff *mNewStuff;
    ///Set the correct buttons on the second toolbar according to the language
    void loadLangToolBar();
    ///All the special characters from a language file, these characters will be as buttons on the Special Characters Toolbar
    QStringList allData;

    protected slots:
    ///Call the Get New Stuff dialog
    void slotDownloadNewStuff();
    ///Hide/Show the menubar
    void slotMenubar();
    ///Set the new font and the new timers
    void slotUpdateSettings();
    ///Set the new level
    void slotChangeLevel(int);
    ///Switch to the grown-up look, menubar is shown
    void slotModeGrownup();
    ///Switch to the kid look, menubar is hidden
    void slotModeKid();
    ///Change Look from menu Look
    void slotChangeTheme(int);
    ///Display the Configure KLettres dialog
    void optionsPreferences();
    ///Load the configuration settings and apply them
    void loadSettings();
    ///When a button is clicked on the characters toolbar, the corresponding character is written in the lineedit 
    void slotPasteChar();
};

#endif // KLETTRES_H
