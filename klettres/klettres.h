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

    KLettres();

    virtual ~KLettres();

	QLabel *langLabel;
	QLabel *levLabel;
	QFont newFont;

	KToolBar *tb;
	KComboBox *lev_comb;
	KComboBox *lang_comb;

	QString language, langString, style;
	QFile lev1File;
	int length, input, num, numRead;
	bool menuBool;
	bool kidBool;
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
    void optionsConfigureKeys();
    void optionsConfigureToolbars();
    void optionsPreferences();
    void newToolbarConfig();
    void slotMenubar();
    void slotShowM();

    void slotQuit();
    void slotGrownup();
    void slotKid();
    //levels menu
    void slotChangeLevel(int );
    void updateLevMenu(int );
    //language menu
    void changeNumeration(int );
    void updateLangMenu(int );

    void setLang();
    void slotSetFont();
    void slotClickApply();

private:
    void setupAccel();
    void setupActions();

    void readConfig();
    void writeConfig();

private:
    KLettresView *m_view;

    KToggleAction *m_action;

    KSelectAction *language_menu;
};

#endif // _KLETTRES_H_
