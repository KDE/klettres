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
#include <qlabel.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qtimer.h>
#include <qwidget.h>
#include <qfile.h>
#include <qtextstream.h>
//KDE includes
#include <kapp.h>
#include <kaudioplayer.h>
#include <kcombobox.h>
#include <khelpmenu.h>
#include <klineedit.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <kpopupmenu.h>
#include <kstddirs.h>
//C++ includes
#include <stdlib.h>
#include <string.h>
#include <time.h>
//project includes
#include <klettresdlg.h>

/** KLettres is the base class of the project */
class KLettres : public KLettresDlg
{
  Q_OBJECT
  private:
  KHelpMenu *mHelpMenu;

  public:
    /** construtor */
    KLettres(QWidget* parent=0, const char *name=0);
    /** destructor */
    ~KLettres();

public slots: // Public slots
  /** No descriptions */
  void game();
  /** No descriptions */
  void slotNext(int);
  /** No descriptions */
  void slotNiveau();
  /** No descriptions */
  void slotLet2(const QString&);
  /** No descriptions */
  void slotLet3(const QString&);
  /** No descriptions */
  void timer1();
  /** No descriptions */
  void timerDone();
  /** No descriptions */
  void timerDone2();
  /** No descriptions */
  void treat1(const QString&);

signals:
  /** No descriptions */
  void newText( const QString& );

   };

#endif

