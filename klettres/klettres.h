/***************************************************************************
                          klettres.h  -  description
                             -------------------
    begin                : Wed Oct 17 17:12:06 BST 2001
    copyright            : (C) 2001 by Anne-Marie Mahfouf
    email                : annma@kde.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KLETTRES_H
#define KLETTRES_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

//Qt includes
#include <qaccel.h>
#include <qfont.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qfile.h>
#include <qtextstream.h>
#include <qtooltip.h>
//KDE includes
#include <kaction.h>
#include <kapp.h>
#include <kaudioplayer.h>
#include <kcombobox.h>
#include <kconfig.h>
#include <kdebug.h>
#include <khelpmenu.h>
#include <klineedit.h>
#include <klocale.h>
#include <kmainwindow.h>
#include <kmessagebox.h>
#include <kmenubar.h>
#include <kpopupmenu.h>
#include <kstatusbar.h>
#include <kstdaction.h>
#include <kstddirs.h>
#include <ktoolbar.h>
//C++ includes
#include <stdlib.h>
#include <string.h>
#include <time.h>
//project includes

/** KLettres is the base class of the project */
class KLettres : public KMainWindow
{
  Q_OBJECT
  private:
  KHelpMenu *mHelpMenu;

  public:
    /** construtor */
    KLettres(QWidget* parent=0, const char *name=0);
    /** destructor */
    ~KLettres();
 	void play();
	QString string1, string2, dataString;
	QString language, langString;
	QFile lev1File;
	int l1, l2, length, input, num, numRead;

	KSelectAction *language_menu;	
	KSelectAction *levels_menu;	
	KToggleAction *m_action;
	KToggleAction *t_action;
   KConfig *config;
	void setupActions();
	
	KComboBox* lev_comb;
	KComboBox* lang_comb;
	QLabel* button1;
    QLineEdit* line1;
	QLabel *langLabel;
	QLabel *levLabel;

public slots: // Public slots
  /** No descriptions */
  void game();
  /** No descriptions */
  void slotNext(int);
  /** No descriptions */
  void slotLet2(const QString&);
  /** No descriptions */
  void timer1();
  /** No descriptions */
  void timerDone();
  /** No descriptions */
  void treat1(const QString&);
  /** No descriptions */
  void slotBackground();
  /** Choose Dutch */
  void slotDutch();
  /** Choose French */
  void slotFrench();
  /** Update the Settings->Choose Language menu **/
  void updateLangMenu(int);

  void changeNumeration(int);
  /** No descriptions */
  void slotQuit();
  /** Hide and Show the ToolBar */
  void slotToolbar();
  /** Hide and show the MenuBar */
  void slotMenubar();
  /** Update the Levels menu **/
  void updateLevMenu(int);

signals:
  /** No descriptions */
  void newText( const QString& );
};

#endif

