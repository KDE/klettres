/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#ifndef _KLETTRES_H_
#define _KLETTRES_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qfont.h>
#include <qlabel.h>
//KDE headers
#include <kapplication.h>
#include <kmainwindow.h>
//Project headers
#include "klettresview.h"

class KToggleAction;
class KSelectAction;
class KToolBar;
class KComboBox;


/**
 * This class serves as the main window for KLettres.  It handles the
 * menus, toolbars, and status bars.
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
    ///Combobox that holds the different languages in the toolbar
    KComboBox *lang_comb;
    ///Holds the i18n current language
   QString language;
   ///holds the non i18n language, style is the background mode, either kid or grownup
   QString langString, style;
   //holds the file from which the letters or syllables are read
   QFile lev1File;
   int length, input, num, numRead;
   ///is false when menubar button is not shown
   bool menuBool;
   ///is false when kid button not shown
   bool kidBool;
   ///is false when grownup button not shown
   bool grownBool;

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
     * recreate our GUI, and re-apply the settings (e.g. "text under icons", etc.)
     */
    void newToolbarConfig();

    ///Hide and show the MenuBar, called by Settings->Show Menubar
    void slotMenubar();

    ///Show menuBar, called by the MenuBar button which is only visible when the menubar is not shown
    void slotShowM();

    ///Save configuration and quits KLettres
    void slotQuit();

    ///Switch to the grown-up look, menubar is shown
    void slotGrownup();

    ///Switch to the kid look, menubar is hidden
    void slotKid();

    ///When the user change levels
    void slotChangeLevel(int );

    ///Update the level menu and combobox
    void updateLevMenu(int );

    ///wWhen the user changes language
    void changeNumeration(int );

    ///Update the language menu and language combobox
    void updateLangMenu(int );

    ///Set current language in menu and combobox
    void setLang();

    ///Set current font in LineEdit line1 and PushButton button1 in KLettresView
    void slotSetFont();

    ///When Apply button in Preferences dialog is clicked, refresh view
    void slotClickApply();

private:
    ////Enable accel keys
    void setupAccel();

    ///Setup our actions using klettresui.rc
    void setupActions();

   /**Read settings from KLettres config file
    *If no config file found, put French as default
    */
    void loadSettings();

    ///Write settings in config file
    void writeConfig();

private:
    ///Call an instance of the KLettresView widget
    KLettresView *m_view;

    ///Action that enables the ShowMenuBar item in the Settings menu
    KToggleAction *m_action;

    ///Action that sets up the Language menu
    KSelectAction *language_menu;
};

#endif // _KLETTRES_H_
