/*
 * Copyright (C) 2003 Anne-Marie Mahfouf <annma@kde.org>
 */

//Qt headers
#include <qfont.h>
#include <qlayout.h>
#include <qtextstream.h>
#include <qtimer.h>
#include <qtooltip.h>
//KDE headers
#include <kaudioplayer.h>
#include <kdebug.h>
#include <kglobalsettings.h>
#include <klocale.h>
#include <kmessagebox.h>
#include <klocale.h>
//C++ includes
#include <stdlib.h>
#include <string.h>
#include <time.h>
//Project headers
#include "klettresview.h"

KLettresView::KLettresView(QWidget *parent)
    : QWidget(parent)
{
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
    QToolTip::add( button1, i18n( "You must type the letter you hear and/or see in the field below" ) );
    //lineEdit for user input
    line1 = new QLineEdit( this, "line1" );
    line1->setGeometry( QRect( 40, 310, 161, 160 ) );
    QToolTip::add( line1, i18n( "Type the letter that you just heard" ) );

    //font for button and lineEdit
    //use largeFont()
    QFont f(KGlobalSettings::largeFont());
    f.setBold(true);
    button1->setFont( f );
    line1->setFont(f);
    //load background pics
    pm_a.load(locate("data","klettres/pics/background1.png"));
    pm_k.load(locate("data","klettres/pics/klettres_back.jpeg"));
    //maybe a warning if background pics are not found
    n = 0;
}

KLettresView::~KLettresView()
{
}

void KLettresView::slotGrownup()
{
    style="grownup";
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
    style="kid";
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
	n=rand()%l1;     //choose a random number
	dataString=QString("klettres/%1/data/level1.txt").arg(langLoc);  //dataString holds the data file name
	string2=QString("klettres/%1/alpha/a-%2.mp3").arg(langLoc).arg(n);
	 play();

    	QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
   	 QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
    }

    if (niveau==3)
	button1->show();

    if (niveau==4)
	button1->hide();

    if (niveau==3 || niveau==4)
    {
	srand((unsigned int)time((time_t *)NULL));
	n=rand()%l2;
	dataString=QString("klettres/%1/data/level3.txt").arg(langLoc);  //dataString holds the data file name
	string2=QString("klettres/%1/syllab/ad-%2.mp3").arg(langLoc).arg(n);
        play();
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

void KLettresView::treat1(const QString& p)
{
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	a1=line1->text();         //get text from LineEdit
   	t1 = a1.upper();    //put it in uppercase
	line1->selectAll();
	line1->cut();
	line1->setText(t1);     //display it in uppercase
	if (niveau==2)
		button1->hide();
	emit newText(p);
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timer1()) );
	timer->start( 2000, TRUE );
}

void KLettresView::timer1()
{
	line1->selectAll();
	if ((button1->text())==t1)
	{
		srand((unsigned int)time((time_t *)NULL));
		n=rand()%l1;
		dataString=QString("klettres/%1/data/level1.txt").arg(langLoc);
		string2=QString("klettres/%1/alpha/a-%2.mp3").arg(langLoc).arg(n);
		play();
	}
	else
	{
		if (niveau==2)
		button1->show(); //show letter after first miss

		string2=QString("klettres/%1/alpha/a-%2.mp3").arg(langLoc).arg(n);    //replay sound
		string1=locate("data",string2);                //of letter
		KAudioPlayer::play(string1);
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
	timer->start( 1000, TRUE );
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
      			if (niveau==4)
			button1->hide();
			game();  //another syllable
		}
	}
	else   //if not, cut it
	{
		line1->backspace();  //delete the char to the left  and position curseur accordingly
		line1->setFocus();
		//play sound again
		string2=QString("klettres/%1/syllab/ad-%2.mp3").arg(langLoc).arg(n);
		string1=locate("data",string2);
		KAudioPlayer::play(string1);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}
}

/**Play the sound and display the letter/syllable*/
void KLettresView::play()
{
		input=1;
      lev1File.setName(locate("data",dataString));
       if (!lev1File.exists()) //if the data files are not installed in the correct dir
         {
					QString mString=i18n("File $KDEDIR/share/apps/%1 not found!\n"
                                                  "Check your installation, please!").arg(dataString);
					KMessageBox::sorry( this, mString,
		                    i18n("KLettres - Error") );
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
		length=st.length();
		string1=locate("data",string2);
		 if (!string1) //if the sound files are not installed  correctly
         {
					QString mString=i18n("File $KDEDIR/share/apps/%1 not found!\n"
                                                  "Check your installation, please!").arg(string2);
					KMessageBox::sorry( this, mString,
		                    i18n("KLettres - Error") );
					exit(1);
			}
		KAudioPlayer::play(string1);
}

#include "klettresview.moc"
