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
	QPixmap *pm = new QPixmap(locate("data","klettres/pics/klsplash.jpeg"));
	QPainter painter;
	painter.begin(pm);
	QFont p_font("helvetica", 20);
	painter.setFont(p_font);
	painter.drawText(260, 200, 120, 50, Qt::AlignCenter, i18n("KLettres") );
	painter.end();
	setBackgroundPixmap(*pm);
	setGeometry(QApplication::desktop()->width ()/2-200,
	            QApplication::desktop()->height()/2-124, 400, 248);
	setFrameStyle( QFrame::Box | QFrame::Raised );
	setLineWidth(1);
	show();
	//play the welcome sound!
	/** Must shorten the sound
	QString string1;
	string1=locate("data","klettres/splash2.mp3");
	KAudioPlayer::play(string1);   **/

	//allow the splash screen to be displayed for 3 seconds
	QTimer *timer = new QTimer(this);
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(slotHide()) );
	timer->start( 1200, TRUE );
}

KhSplash::~KhSplash()
{}


/** Hide the splash screen and call the game */
void KhSplash::slotHide()
{
	   this->hide();
		klettres = new KLettres();
		//klettres->language=langString;//holds the language string
		//klettres->l1=l1;  //number of sounds for levels 1 and 2 related to the language
		//klettres->l2=l2; //numbers of sounds for level 3 and 4  related to the language
//		klettres->game();
		//klettres->show();
}

#include "khsplash.moc"
