/*
 * Copyright (C) 2001-2004 Anne-Marie Mahfouf <annma@kde.org>

    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

//Qt headers
#include <qtimer.h>
#include <qtooltip.h>
//KDE headers
#include <kapplication.h>
#include <klocale.h>
//C++ includes
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Project headers
#include "klettres.h"
#include "klettresview.h"
#include "prefs.h"

KLettresView::KLettresView(KLettres *parent)
    : QWidget(parent)
{
    klettres = parent;

    setMinimumSize( QSize( 640, 538 ) );
    setMaximumSize( QSize( 640, 538 ) );

    //Button with letter or syllable
    button1 = new QLabel( this, "button1" );
    button1->setGeometry( QRect( 50, 100, 160, 160 ) );
    cg.setColor( QColorGroup::Foreground, white );
    cg.setColor( QColorGroup::Background, QColor(53,87,158));
    pal.setActive( cg );
    button1->setPalette( pal );
    button1->setText( i18n( "A" ) );
    QToolTip::add( button1, i18n( "You must type the letter/syllable you hear and/or see in the field below" ) );
    //lineEdit for user input
    line1 = new QLineEdit( this, "line1" );
    line1->setGeometry( QRect( 40, 310, 161, 160 ) );
    QToolTip::add( line1, i18n( "Type the letter or syllable that you just heard" ) );

    //load background pics
    pm_a.load(locate("data","klettres/pics/background1.png"));
    pm_k.load(locate("data","klettres/pics/klettres_back.jpeg"));
    //maybe a warning if background pics are not found
    n = 0;
    temp=-1;

}

KLettresView::~KLettresView()
{
}

void KLettresView::slotGrownup()
{
    Prefs::setStyle(Prefs::EnumStyle::grownup);
    Prefs::writeConfig();
    setMinimumSize( QSize( 640, 480 ) );
    setMaximumSize( QSize( 640, 480 ) );
    setBackgroundPixmap(pm_a);
    //button1 background
    cg.setColor( QColorGroup::Foreground, white );
    cg.setColor( QColorGroup::Background, QColor(53,87,158));
    pal.setActive( cg );
    button1->setPalette( pal );
}

void KLettresView::slotKid()
{
    Prefs::setStyle(Prefs::EnumStyle::kid);
    Prefs::writeConfig();
    setMinimumSize( QSize( 640, 480 ) );
    setMaximumSize( QSize( 640, 480 ) );
    setBackgroundPixmap(pm_k);
    //change button1 background
    cg.setColor( QColorGroup::Foreground, white );
    cg.setColor( QColorGroup::Background, black);
    pal.setActive( cg );
    button1->setPalette( pal );
}

void KLettresView::game()
{
 //reset everything so when you change language or levels
 //it all restart nicely
 QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
 input = 1;
 line1->clear();
 line1->setCursorPosition(0);
 line1->setFocus();

 if (Prefs::level()==1)
	button1->show();

    if (Prefs::level()==2)
	button1->hide();

    if (Prefs::level()==1||Prefs::level()==2)
    {
	button1->setMinimumSize( QSize( 200, 160 ) );
	button1->setMaximumSize( QSize( 200, 160 ) );
	line1->setMinimumSize( QSize( 140, 160 ) );
	line1->setMaximumSize( QSize( 140, 160 ) );
	chooseSound();

    	QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
   	 QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
    }

    if (Prefs::level()==3)
	button1->show();

    if (Prefs::level()==4)
	button1->hide();

    if (Prefs::level()==3 || Prefs::level()==4)
    {
        chooseSound();
	if (length==2)
	{
		button1->setMinimumSize( QSize( 200, 160 ) );
		button1->setMaximumSize( QSize( 200, 160 ) );
		line1->setMinimumSize( QSize( 200, 160 ) );
		line1->setMaximumSize( QSize( 200, 160 ) );
	}
       	if (length==3)
	{
		button1->setMinimumSize( QSize(250, 160 ) );
		button1->setMaximumSize( QSize( 250, 160 ) );
		line1->setMinimumSize( QSize( 250, 160 ) );
		line1->setMaximumSize( QSize( 250, 160 ) );
	}
	QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	}
	line1->setMaxLength( 1 );
	line1->setCursorPosition(0);
	line1->setFocus();
}

void KLettresView::treat1(const QString& )
{
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	a1=line1->text();   //get text from LineEdit
	if (!a1.at(0).isLetter()) //if it's not a letter which was typed
	{
	QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}
   	t1 = a1.upper();    //put it in uppercase
	line1->selectAll();
	line1->cut();
	line1->setText(t1);     //display it in uppercase
	if (Prefs::level()==2)
		button1->hide();
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timer1()) );
	timer->start( m_timer*100, TRUE );
}

void KLettresView::timer1()
{
	line1->selectAll();
	if ((button1->text())==t1)
	{
		chooseSound();
	}
	else
	{
		if (Prefs::level()==2)
		button1->show(); //show letter after first miss
		klettres->soundFactory->playSound(n);//replay sound
	}

	line1->cut();

	QObject::connect(line1, SIGNAL(textChanged(const
 				QString&)),this,SLOT(treat1(const QString&)) );
	line1->setFocus();
}

//levels 3 and 4
void KLettresView::slotLet2(const QString& )
{
	line1->clearFocus();
	//disconnect
	QObject::disconnect(line1, SIGNAL(textChanged(const
 		QString&)),this,SLOT(slotLet2(const QString&)) );

	line1->setSelection(input-1,1);
	a1=line1->selectedText();   //get the input letter
	t1 = a1.upper(); //input in uppercase
	line1->cut();
	line1->setText(line1->text()+t1);
  	t1=line1->text(); //t1 is the whole lineEdit text now
	sj=st.left(input);
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timerDone()) );
	timer->start( m_timer*100, TRUE );
}

void KLettresView::timerDone()
{
	if (t1==sj)   //if letter input is correct
	{
	   if (sj!=st)  //if text in lineEdit not equal to text on button
		{            //i.e if you still have to allow input
			line1->setMaxLength( input+1 );
			line1->setCursorPosition( input );
			line1->setFocus();
			input++;
			QObject::connect(line1, SIGNAL(textChanged(const
 					QString&)),this,SLOT(slotLet2(const QString&)) );
       }
		else
		{
			line1->selectAll();
			line1->cut();
			line1->setCursorPosition(0 );
			line1->setFocus();
			line1->setMaxLength( 1 );
      			if (Prefs::level()==4)
			button1->hide();
			game();  //another syllable
		}
	}
	else   //if not, cut it
	{
		line1->backspace();  //delete the char to the left  and position curseur accordingly
		line1->setFocus();
		//play sound again
		klettres->soundFactory->playSound(n);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}
}

void KLettresView::chooseSound()
{
	input =1;
        //If there are no sounds loaded
        if (klettres->soundFactory->sounds ==0)
        	return;
	n=kapp->random()%(klettres->soundFactory->sounds);//l;
	//have not 2 same sounds consecutively
	if (temp<0)
		temp=n;
	else
	{
		while (n==temp)
			n=kapp->random()%(klettres->soundFactory->sounds);
		temp=n;
	}

        //The sound is played
        klettres->soundFactory->playSound(n);
        //The letter/syllable is displayed
        button1->setText(klettres->soundFactory->namesList[n]);
        //store letter or syllable in st
        st = klettres->soundFactory->namesList[n];
        //Find the length of the syllable
        length=klettres->soundFactory->namesList[n].length();
}

#include "klettresview.moc"
