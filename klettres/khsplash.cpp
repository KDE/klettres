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
#include <kstandarddirs.h>
#include <qcursor.h>
#include "khsplash.h"

KhSplash::KhSplash(QWidget *parent, const char *name ) : QFrame(parent,name,QWidget::WStyle_NoBorder | QWidget::WStyle_Customize)
{
	QPixmap pm;
	pm.load(locate("data","klettres/pics/klettres_splash.png"));
	setBackgroundPixmap(pm);
	int screen = QApplication::desktop()->screenNumber(QCursor::pos());
	QRect geom = QApplication::desktop()->screenGeometry(screen);
	setGeometry(geom.width()/2-200+geom.x(),
	            geom.height()/2-124+geom.y(), 400, 248);
	setFrameStyle( QFrame::Box | QFrame::Raised );
	setLineWidth(1);
	show();
	//play the welcome sound!
	QString string1;
	string1=locate("data","klettres/sounds/splash2.mp3");
	KAudioPlayer::play(string1);

	//allow the splash screen to be displayed for 3 seconds
	QTimer *timer = new QTimer(this);
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(slotHide()) );
	timer->start( 3000, TRUE );
}

KhSplash::~KhSplash()
{}


/** Hide the splash screen and call the game */
void KhSplash::slotHide()
{
	this->hide();
	KLettres *klettres = new KLettres();
	klettres->show();
}

#include "khsplash.moc"
