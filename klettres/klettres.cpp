/***************************************************************************
                          klettres.cpp  -  description
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

#include "klettres.h"

QString s[26], sd[30], a1,t1,sb,s1,sj, st;
int n=0, niveau=1;

KLettres::KLettres(QWidget *parent, const char *name) : KLettresDlg(parent, name)
{
	QAccel *a = new QAccel( comb1 );        // create accels for comb1
	a->connectItem( a->insertItem(Key_L+ALT), // adds ALT+N accelerator
	                this,                  // connected to this'
	                SLOT(slotNiveau()) );

	quitte->setGeometry( QRect( 555, 12, 77, 34 ) );

	// signals and slots connections
	connect( comb1, SIGNAL( activated(int) ), this, SLOT( slotNext(int) ) );
	QObject::connect( quitte, SIGNAL( clicked() ), kapp, SLOT( quit() ) );
	// Set up the help menu
   	mHelpMenu = new KHelpMenu(this, KGlobal::instance()->aboutData(), true);
	aide->setPopup(mHelpMenu->menu());

	QPixmap pm;
	pm.load(locate("data","klettres/pics/klettres_back.jpeg"));
	setBackgroundPixmap(pm);

	game();
}


KLettres::~KLettres()
{
}

void KLettres::slotNext(int index)
{
	switch ( index )
	{
	default:
	case 0:
		niveau=1;
		break;

	case 1:
		niveau=2;
		break;

	case 2:
		niveau=3;
		break;

	case 3:
		niveau=4;
		break;
	}
	game();
}

void KLettres::game()
{
	if (niveau==1)
		button1->show();

	if (niveau==2)
		button1->hide();

	if (niveau==1||niveau==2)
	{
		button1->setMinimumSize( QSize( 200, 160 ) );
		button1->setMaximumSize( QSize( 200, 160 ) );
		line1->setMinimumSize( QSize( 140, 160 ) );
		line1->setMaximumSize( QSize( 140, 160 ) );
		srand((unsigned int)time((time_t *)NULL));
		n=rand()%26;
		QFile lev1File(locate("data","klettres/level1.txt"));
		if (!lev1File.exists())
         {
					KMessageBox::sorry( this, i18n("File $KDEDIR/share/apps/klettres/level1.txt not found!\n"
                                                  "Check your installation, please!"),
		                    "KLettres - Error" );
					exit(1);
			}
		lev1File.open(IO_ReadOnly);
		QTextStream namesStream( &lev1File);
		QString nameString;
		int count=0;
		while (namesStream.atEnd()==0)
		{
			//read one line from the text
			nameString=namesStream.readLine();
			if (count==n)
				st=nameString; //store the choosen word in variable st
			count++ ;
		}
		lev1File.close();
		button1->setText(st);
		QString string1;
		QString string2;
		string2.sprintf("klettres/sons/a-%i.wav",n);
		string1=locate("data",string2);
		KAudioPlayer::play(string1);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
		QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}

	if (niveau==3)
		button1->show();

	if (niveau==4)
		button1->hide();

	if (niveau==3||niveau==4)
	{
//		lab1->setText("Listen and type the sound");
		//button1->show();
		button1->setMinimumSize( QSize( 250, 160 ) );
		button1->setMaximumSize( QSize( 250, 160 ) );
		line1->setMinimumSize( QSize( 250, 160 ) );
		line1->setMaximumSize( QSize( 250, 160 ) );
		srand((unsigned int)time((time_t *)NULL));
		n=rand()%26;
		QFile lev1File(locate("data","klettres/level3.txt"));
		if (!lev1File.exists())
         {
					KMessageBox::sorry( this, i18n("File $KDEDIR/share/apps/klettres/level3.txt not found!\n"
                                                  "Check your installation, please!"),
		                    "KLettres - Error" );
					exit(1);
			}
		lev1File.open(IO_ReadOnly);
		QTextStream namesStream( &lev1File);
		QString nameString;
		int count=0;
		while (namesStream.atEnd()==0)
		{
			//read one line from the text
			nameString=namesStream.readLine();
			if (count==n)
				st=nameString; //store the choosen word in variable st
			count++ ;
		}
		lev1File.close();
		button1->setText(st);

		QString string1;
		QString string2;
		string2.sprintf("klettres/sons2/ad-%i.wav",n);
		string1=locate("data",string2);
		KAudioPlayer::play(string1);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
		QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	}
	line1->setMaxLength( 1 );
	line1->setCursorPosition(0);
	line1->setFocus();
}

void KLettres::treat1(const QString& p)
{
	if (niveau==2)
		button1->hide();
	emit newText(p);
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timer1()) );
	timer->start( 2000, TRUE );
}

void KLettres::timer1()
{
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	line1->selectAll();
	QString tl1,al1;
	al1=line1->text();
   tl1.sprintf(al1.upper().latin1());
	if ((button1->text())==tl1)
	{
		srand((unsigned int)time((time_t *)NULL));
		n=rand()%26;
		QFile lev1File(locate("data","klettres/level1.txt"));
		if (!lev1File.exists())
         {
					KMessageBox::sorry( this, i18n("File $KDEDIR/share/apps/klettres/level1.txt not found!\n"
                                                  "Check your installation, please!"),
		                    "KLettres - Error" );
					exit(1);
			}
		lev1File.open(IO_ReadOnly);
		QTextStream namesStream( &lev1File);
		QString nameString;
		int count=0;
		while (namesStream.atEnd()==0)
		{
			//read one line from the text
			nameString=namesStream.readLine();
			if (count==n)
				st=nameString; //store the choosen word in variable st
			count++ ;
		}
		lev1File.close();
		button1->setText(st);
	}
	else if (niveau==2)
		button1->show();
	line1->cut();

	QString string1;
	QString string2;
	string2.sprintf("klettres/sons/a-%i.wav",n);
	string1=locate("data",string2);
	KAudioPlayer::play(string1);

	QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	line1->setFocus();
}


void KLettres::slotLet2(const QString& s)
{
	emit newText(s);
	line1->clearFocus();
	//disconnect
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	//test the first letter
	char c[1];
	a1=line1->text();
	t1.sprintf(a1.upper().latin1());
	sb=button1->text();
	strncpy(c,sb.latin1(),1);
	sj.sprintf("%c",c[0]);
	//line1->selectAll();
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timerDone()) );
	timer->start( 1000, TRUE );
}


/** No descriptions */
void KLettres::timerDone()
{
	if (t1==sj)
	{
		//line1->deselect();
		line1->setMaxLength( 2 );
		line1->setCursorPosition( 1 );
		line1->setFocus();
		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet3(const QString&)) );
	}
	else
	{
		line1->selectAll();
		line1->cut();
		line1->setCursorPosition(0);
		line1->setFocus();
		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}
}

void KLettres::slotLet3(const QString& s)
{
	emit newText(s);
	line1->clearFocus();
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet3(const QString&)) );

	a1=line1->text();
	t1.sprintf(a1.upper().latin1());
	s1=button1->text();
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timerDone2()) );
	timer->start( 2000, TRUE );
}

void KLettres::timerDone2()
{
	if (t1==s1)
	{
		line1->selectAll();
		line1->cut();
		line1->setCursorPosition(0 );
		line1->setFocus();
		line1->setMaxLength( 1 );
		//changer button1->text()
		srand((unsigned int)time((time_t *)NULL));
		n=rand()%28;
		QFile lev1File(locate("data","klettres/level3.txt"));
		if (!lev1File.exists())
         {
					KMessageBox::sorry( this, i18n("File $KDEDIR/share/apps/klettres/level3.txt not found!\n"
                                                  "Check your installation, please!"),
		                    "KLettres - Error" );
					exit(1);
			}
		lev1File.open(IO_ReadOnly);
		QTextStream namesStream( &lev1File);
		QString nameString;
		int count=0;
		while (namesStream.atEnd()==0)
		{
			//read one line from the text
			nameString=namesStream.readLine();
			if (count==n)
				st=nameString; //store the choosen word in variable st
			count=count+1 ;
		}
		lev1File.close();
		button1->setText(st);

		QString string1;
		QString string2;
		string2.sprintf("klettres/sons2/ad-%i.wav",n);
		string1=locate("data",string2);
		KAudioPlayer::play(string1);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}
	else
	{
		//suppress the second letter
		line1->setSelection(1,1);
		line1->cut();
		line1->setCursorPosition(1);
		line1->setFocus();
		button1->show();

		QString string1;
		QString string2;
		string2.sprintf("klettres/sons2/ad-%i.wav",n);
		string1=locate("data",string2);
		KAudioPlayer::play(string1);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet3(const QString&)) );
	}
	if (niveau==4)
		button1->hide();
}

void KLettres::slotNiveau()
{
	if ((niveau==1)||(niveau==2)||(niveau==3))
		niveau++;
	else
	{
		if (niveau==4)
			niveau--;
	}
	comb1->setCurrentItem( niveau-1 );
	game();
}

#include "klettres.moc"
