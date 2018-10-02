/***************************************************************************
 *   Copyright 2001-2008 by Anne-Marie Mahfouf                              *
 *   annma@kde.org                                             *
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

#include <KXmlGuiWindow>

#include "klettresview.h"
#include "soundfactory.h"

class QLabel;
class KToggleAction;
class KSelectAction;
class KToolBar;
class KLNewStuff;

/**
 * @short Application Main Window
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 2.1
 */
class KLettres : public KXmlGuiWindow
{
    Q_OBJECT
public:

    ///Constructor
    KLettres();
    ///Destructor
    virtual ~KLettres();

    ///Sound class
    SoundFactory *soundFactory = nullptr;
    ///All available language names
    QStringList m_languageNames;
    /**
    *Load the xml file
    *@param layoutDocument the xml file
    *@return bool true if the xml document is found and well formed, false otherwise
    */
    bool loadLayout(QDomDocument &layoutDocument);
    ///Action that sets up the Language menu
    KSelectAction *m_languageAction = nullptr;

    public Q_SLOTS:
    ///Set the new language
    void slotChangeLanguage(int);
    ///Set the new level
    void slotChangeLevel(int);

protected:
    ///Call an instance of the KLettresView widget
    KLettresView *m_view;
    ///Action that enables the ShowMenuBar item in the Settings menu
    KToggleAction *m_menubarAction;
    ///Action that sets up the Level menu
    KSelectAction *m_levelAction;
    ///Action that sets up the Look menu
    KSelectAction *m_themeAction;
    ///Action allowing the Kid mode
    KToggleAction *m_kidAction;
    ///Action allowing the Grownup mode
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
    KToolBar *specialCharToolbar;
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
    QIcon charIcon(QChar c);
    /**
     *Update the level menu and level combobox
     * @param id The id of the new level
     */
    void updateLevMenu(int id);
    ///Create a KNewStuff instance
    KLNewStuff *mNewStuff = nullptr;
    ///Set the correct buttons on the second toolbar according to the language
    void loadLangToolBar();
    ///All the special characters from a language file, these characters will be as buttons on the Special Characters Toolbar
    QStringList allData;

    protected Q_SLOTS:
    ///Call the Get New Stuff dialog
    void slotDownloadNewStuff();
    ///Hide/Show the menubar
    void slotMenubar();
    ///Set the new font and the new timers
    void slotUpdateSettings();
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
