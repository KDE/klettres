/***************************************************************************
                          klettres.h  -  description
                             -------------------
    begin                : Thu Feb 15 12:17:03 GMT 2001
    copyright            : (C) 2001 by Anne-Marie Mahfouf
    email                : a-m.mahfouf@lineone.net
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
#include <qpushbutton.h>
#include <qtimer.h>
#include <qwidget.h>
//KDE includes
#include <kapp.h>
#include <kcombobox.h>
#include <klineedit.h>
//C++ includes
#include <stdlib.h>
#include <string.h>
#include <time.h>
//project includes
#include <klettresdlg.h>
#include <kaudioplayer.h>
#include <kstddirs.h>
#include <qfile.h>
#include <qtextstream.h>

/** KLettres is the base class of the project */
class KLettres : public KLettresDlg
{
  Q_OBJECT 
  public:
    /** construtor */
    KLettres(QWidget* parent=0, const char *name=0);
    /** destructor */
    ~KLettres();
public slots: // Public slots
  /** No descriptions */
  void game();
  /** No descriptions */
  void slotAide();
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
