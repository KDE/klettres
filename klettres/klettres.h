/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#ifndef _KLETTRES_H_
#define _KLETTRES_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

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
    void optionsShowToolbar();
    void optionsShowStatusbar();
    void optionsConfigureKeys();
    void optionsConfigureToolbars();
    void newToolbarConfig();
	void slotMenubar();
	void slotShowM();

	void slotQuit();
	void slotGrownup();
	void slotKid();
	//look and feel menu
	void changeLook(int );
	void updateLookMenu(int );
	//levels menu
	void slotNext(int );
	void updateLevMenu(int );
	//language menu
	void changeNumeration(int );
	void updateLangMenu(int );

	void setLang();

private:
    void setupAccel();
    void setupActions();

	void readConfig();
	void writeConfig();

private:
    KLettresView *m_view;

    KToggleAction *m_toolbarAction;
    KToggleAction *m_statusbarAction;

	KToggleAction *m_action;

	KSelectAction *levels_menu;
	KSelectAction *language_menu;
	KSelectAction *look_menu;
};

#endif // _KLETTRES_H_
