/***************************************************************************
                          khsplash.cpp  -  description
                             -------------------
    begin                : Fri Jul 27 2001
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

#include <kaudioplayer.h>
#include <kstddirs.h>

#include "khsplash.h"

KhSplash::KhSplash(QWidget *parent, const char *name ) : QFrame(parent,name,QWidget::WStyle_NoBorder | QWidget::WStyle_Customize)
{
   QPixmap pm;
   pm.load(locate("data","klettres/pics/klettres-main.png"));
	setBackgroundPixmap(pm);
   setGeometry(QApplication::desktop()->width ()/2-320,
 				QApplication::desktop()->height()/2-240, 640, 480);
   setFrameStyle( QFrame::Box | QFrame::Raised );
	setLineWidth(1);
	show();
   //play the welcome sound!
   QString string1;
   string1=locate("data","klettres/sounds/splash2.mp3");
   KAudioPlayer::play(string1);

    //allow the splash screen to be displayed for 9 seconds
    QTimer *timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()),
    this, SLOT(slotAnother()) );
    timer->start( 3000, TRUE );
}

KhSplash::~KhSplash(){
}

/** Call another splash screen */
void KhSplash::slotAnother()
{

	QPixmap pm;
	pm.load(locate("data","klettres/pics/klettres-main2.png"));
	setBackgroundPixmap(pm);
    QTimer *timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()),
    this, SLOT(slotHide()) );
    timer->start( 6000, TRUE );
}


/** Hide the splash screen and call the game */
void KhSplash::slotHide()
{
    this->hide();
    KLettres *klettres = new KLettres();
    klettres->show();
}

#include "khsplash.moc"
