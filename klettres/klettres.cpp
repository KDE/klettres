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
#include "version.h"

#include <kglobalsettings.h>

QString s[30], sd[30], a1, t1, sb, s1, sj, st;
int n=0, niveau=1;

KLettres::KLettres(QWidget *parent, const char *name) : KMainWindow(parent, name)
{
   setCaption( i18n( "KLettres - version %1" ).arg(KLETTRES_VERSION) );

	//Actions
	setupActions();
	m_action->setChecked(true);
	t_action->setChecked(true);

   //stringlist for language combo
        lang_list.append(i18n("Danish"));
	lang_list.append(i18n("Dutch"));
	lang_list.append(i18n("French"));
   //Settings->Choose Language menu
	QStringList language_list;
	language_list.append(i18n("D&anish"));
	language_list.append(i18n("&Dutch"));
	language_list.append(i18n("F&rench"));
	language_menu = new KSelectAction(i18n("Learning L&anguage"), 0, actionCollection(), "languages");
	language_menu->setItems(language_list);
   connect(language_menu, SIGNAL(activated(int)), this, SLOT(changeNumeration(int)));
   connect(language_menu, SIGNAL(activated(int)), this, SLOT(updateLangMenu(int)));
   //Settings->Look & Feel menu
	QStringList look_list;
        look_list.append(i18n("&Grown-Up"));
	look_list.append(i18n("&Kids"));
	look_menu = new KSelectAction(i18n("Look && &Feel"), 0, actionCollection(), "look_feel");
        look_menu->setItems(look_list);
   connect(look_menu, SIGNAL(activated(int)), this, SLOT(changeLook(int)));
   connect(look_menu, SIGNAL(activated(int)), this, SLOT(updateLookMenu(int)));	
   //Levels menu
	QStringList levels_list;
	levels_list.append(i18n("Level 1"));
	levels_list.append(i18n("Level 2"));
	levels_list.append(i18n("Level 3"));
	levels_list.append(i18n("Level 4"));
	levels_menu = new KSelectAction(i18n("&Levels"), 0, actionCollection(), "levels");
	levels_menu->setItems(levels_list);
	levels_menu->setCurrentItem(0);//default=level1 when start
   connect(levels_menu, SIGNAL(activated(int)), this, SLOT(slotNext(int)));
   connect(levels_menu, SIGNAL(activated(int)), this, SLOT(updateLevMenu(int)));

	createGUI(locate("data", "klettres/klettresui.rc"));

	/*** GUI ***/
	tb = toolBar("mainToolBar");
	//Levels comboBox
	lev_comb= new KComboBox(tb);
	lev_comb->insertItem( i18n( "Level 1" ) );
        lev_comb->insertItem( i18n( "Level 2" ) );
        lev_comb->insertItem( i18n( "Level 3" ) );
        lev_comb->insertItem( i18n( "Level 4" ) );
	tb->insertWidget(1, 100, lev_comb,1); //id, width, widget, index
   connect( lev_comb, SIGNAL( activated(int) ), this, SLOT( slotNext(int) ) );

   //font for comboxes 08/09 commented that; try to find a way to make it just one point bigger
	/*QFont f_comb( "times" , 14, QFont::Bold );
	tb->setFont( f_comb );
	lev_comb->setFont( f_comb );*/

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
    //debug font
    QFontInfo info( f );
    QString family = info.family();
	 kdDebug()<<"Button1 font family" <<endl;
	 kdDebug() << family << endl;
	 kdDebug() << "Default family" << endl;
	 kdDebug() << f.defaultFamily() <<endl;
	 kdDebug() << "Size" << endl;              //asked for
	 kdDebug() << f.pointSize() <<endl;
	 kdDebug() << "Size family" << endl;   //real one
	 kdDebug() << info.pointSize() <<endl;

	//Set up StatusBar
	KStatusBar *st=statusBar();
	QFont f_lab( "times" , 14);  //font for statusBar
	langLabel = new QLabel(st);
	levLabel = new QLabel(st);
	st->addWidget(levLabel);
	st->insertFixedItem("", 1);//add a space
	st->addWidget(langLabel);
	// 08/09 levLabel->setFont(f_lab);
        // 08/09  langLabel->setFont( f_lab);
	 //load background pics
	pm_a.load(locate("data","klettres/pics/background1.png"));
	pm_k.load(locate("data","klettres/pics/klettres_back.jpeg"));

      //Read config TODO a read config method
      //if not, put default as French
        config = kapp->config();
	 config->setGroup("Language");
	 langString=config->readEntry("MyLanguage");
	 numRead=config->readNumEntry("Number");
	 num=numRead;
	 style=config->readEntry("myStyle");
	 if (!langString) //if there is no config file
	 {
		QString mString=QString(i18n("This is the first time you have run KLettres.\n"
                                                  "The default learning language is set to French.\n"
																"You can change the language in the Settings menu.\n\n"
																"Default level is Level 1, the easiest one.\n"
																"You can change the level in the Levels menu."));
		KMessageBox::information( this, mString,"KLettres - Default" );
		l1=26;   //set French as default
		l2=28;
		slotGrownup();	//default style==grown-up
		slotFrench();
	 }
	 else
	{
	       config->setGroup("Language");
		language=config->readEntry("MyLanguage");
		config->setGroup(langString);
		l1 =config->readNumEntry("Alphabet");
		l2 =config->readNumEntry("Syllables");
		tb->setCurrentComboItem(2, num);
		language_menu->setCurrentItem(num);
		if (style=="grownup") slotGrownup();
			else slotKid();
               game();
	}
   levLabel->setText(i18n("Current level is %1").arg(niveau));
   langLabel->setText(i18n("Current language is %1").arg(language));
}


KLettres::~KLettres()
{
}

/** When level changes */
void KLettres::slotNext(int id)
{
	switch ( id)
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
	updateLevMenu(id);
	levLabel->setText(i18n("Current level is %1").arg(niveau));
	game();
}

/**main fonction */
void KLettres::game()
{
        if (style=="kid")
	{
        	setMinimumSize( QSize( 640, 538 ) );
        	setMaximumSize( QSize( 640, 538 ) );
	}
	else
	{
        	setMinimumSize( QSize( 640, 525) );
        	setMaximumSize( QSize( 640, 525 ) );
	}
	//08/09 show();
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
		dataString=QString("klettres/%1/data/level1.txt").arg(language);  //dataString holds the data file name
		string2=QString("klettres/%1/alpha/a-%2.mp3").arg(language).arg(n);
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
		dataString=QString("klettres/%1/data/level3.txt").arg(language);  //dataString holds the data file name
		string2=QString("klettres/%1/syllab/ad-%2.mp3").arg(language).arg(n);
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

void KLettres::treat1(const QString& p)
{
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(treat1(const QString&)) );
	QObject::disconnect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	a1=line1->text();         //get text from LineEdit
   t1.sprintf(a1.upper().latin1());    //put it in uppercase
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

void KLettres::timer1()
{
	line1->selectAll();
	if ((button1->text())==t1)
	{
		srand((unsigned int)time((time_t *)NULL));
		n=rand()%l1;
		dataString=QString("klettres/%1/data/level1.txt").arg(language);
		string2=QString("klettres/%1/alpha/a-%2.mp3").arg(language).arg(n);
		play();
	}
	else
	{
		if (niveau==2)
		button1->show(); //show letter after first miss

		string2=QString("klettres/%1/alpha/a-%2.mp3").arg(language).arg(n);    //replay sound
		string1=locate("data",string2);                //of letter
		KAudioPlayer::play(string1);
	}
		
	line1->cut();

	QObject::connect(line1, SIGNAL(textChanged(const
 				QString&)),this,SLOT(treat1(const QString&)) );
	line1->setFocus();
}

//levels 3 and 4
void KLettres::slotLet2(const QString& s)
{
	line1->clearFocus();
	//disconnect
	QObject::disconnect(line1, SIGNAL(textChanged(const
 		QString&)),this,SLOT(slotLet2(const QString&)) );

	line1->setSelection(input-1,1);
//	line1->cursorBackward(true);
	bool test=line1->hasSelectedText();
	kdDebug() << test <<endl;
	a1=line1->selectedText();   //get the input letter
	t1.sprintf(a1.upper().latin1()); //input in uppercase
	line1->cut();
	line1->setText(line1->text()+t1);
    t1=line1->text(); //t1 is the whole lineEdit text now
	sj=st.left(input);
	QTimer *timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()),
	         this, SLOT(timerDone()) );
	timer->start( 1000, TRUE );
}

void KLettres::timerDone()
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
		string2=QString("klettres/%1/syllab/ad-%2.mp3").arg(language).arg(n);
		string1=locate("data",string2);
		KAudioPlayer::play(string1);

		QObject::connect(line1, SIGNAL(textChanged(const
 QString&)),this,SLOT(slotLet2(const QString&)) );
	}
}

/**Play the sound and display the letter/syllable*/
void KLettres::play()
{
		input=1;
      lev1File.setName(locate("data",dataString));
       if (!lev1File.exists()) //if the data files are not installed in the correct dir
         {
					QString mString=QString(i18n("File $KDEDIR/share/apps/%1 not found!\n"
                                                  "Check your installation, please!")).arg(dataString);
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
					QString mString=QString(i18n("File $KDEDIR/share/apps/%1 not found!\n"
                                                  "Check your installation, please!")).arg(string2);
					KMessageBox::sorry( this, mString,
		                    i18n("KLettres - Error") );
					exit(1);
			}
		KAudioPlayer::play(string1);
}

void KLettres::setupActions()
{
   //actions for the File menu
   KStdAction::quit(this, SLOT(slotQuit()), actionCollection());
   //actions for theSettings menu
   (void) new KAction (i18n("D&anish"),0, this, SLOT(slotDanish()), actionCollection(), "danish");
   (void) new KAction (i18n("&Dutch"),0, this, SLOT(slotDutch()), actionCollection(), "dutch");
   (void) new KAction (i18n("&French"),0, this, SLOT(slotFrench()), actionCollection(), "french");
   (void) new KAction (i18n("&Background"),0, this, SLOT(slotBackground()), actionCollection(), "change_background");
   m_action = new KToggleAction(i18n("Show &Menubar"),CTRL+Key_M, this, SLOT(slotMenubar()), actionCollection(), "menubar");
   t_action = new KToggleAction(i18n("Show &ToolBar"),CTRL+Key_T, this, SLOT(slotToolbar()), actionCollection(), "toolbar");
 }

/** Allow the user to change the background */
void KLettres::slotBackground()
{
/** Not Implemented Yet **/
}

/** Update Settings->Choose Language menu */
void KLettres::updateLangMenu(int id)
{
    language_menu->setCurrentItem(id);
    tb->setCurrentComboItem(2, id);
	 //lang_comb->setCurrentItem(id);
}

/** Update Levels menu */
void KLettres::updateLevMenu(int id)
{
	levels_menu->setCurrentItem(id);
	lev_comb->setCurrentItem(id);
}

/** Update Look menu */
void KLettres::updateLookMenu(int id)
{
	look_menu->setCurrentItem(id);
}

void KLettres::changeNumeration(int id)
{
	updateLangMenu(id);
    switch (id) {
        case 0:
            slotDanish();
            break;
        case 1:
            slotDutch();
            break;
	case 2:
            slotFrench();
            break;
    }
}

/** Set language to French */
void KLettres::slotFrench()
{
	language=i18n("French");
	num=2;
	config->setGroup("Language");
	langString=config->readEntry("MyLanguage");
	if ( !langString.isNull() )
	{
 	  	//read config to find l1 and l2
		config->setGroup(language);	
		l1 =config->readNumEntry("Alphabet");
		l2 =config->readNumEntry("Syllables");
	}
	langLabel->setText(i18n("Current language is %1").arg(language));
       language_menu->setCurrentItem(num);
	tb->setCurrentComboItem(2, num);
	game();
}

/** Set Language to Dutch */
void KLettres::slotDutch()
{
	language=i18n("Dutch");
	num=1;
        langLabel->setText(i18n("Current language is %1").arg(language));
	language_menu->setCurrentItem(num);
	tb->setCurrentComboItem(2, num);
	  //read config to find l1 and l2
	config->setGroup("Language");
	langString=config->readEntry("MyLanguage");
	if (langString.isNull())
	{
   		l1=22;
		l2=26;
	}
	else
	{
		config->setGroup(language);
		l1 =config->readNumEntry("Alphabet");
		l2 =config->readNumEntry("Syllables");
	}
   game();
}

/** Set Language to Danish*/
void KLettres::slotDanish()
{
	language=i18n("Danish");
	num=0;
        langLabel->setText(i18n("Current language is %1").arg(language));
	language_menu->setCurrentItem(num);
	tb->setCurrentComboItem(2, num);
	  //read config to find l1 and l2
	config->setGroup("Language");
	langString=config->readEntry("MyLanguage");
	if (langString.isNull())
	{
                l1=29;
		l2=28;
	}
	else
	{
		config->setGroup(language);
		l1 =config->readNumEntry("Alphabet");
		l2 =config->readNumEntry("Syllables");
	}
   game();

}
/** Quit KLettres and write config */
void KLettres::slotQuit()
{
	//write current config
	config->setGroup("Language");
	config->writeEntry("MyLanguage", language);
	config->writeEntry("Number",num);
	config->writeEntry("myStyle", style);
	kdDebug() << style << endl;
	config->setGroup("French");
	config->writeEntry("Alphabet", 26);
        config->writeEntry("Syllables", 28);
	config->setGroup("Dutch");
	config->writeEntry("Alphabet", 22);
        config->writeEntry("Syllables", 26);
	config->setGroup("Danish");
	config->writeEntry("Alphabet", 29);
        config->writeEntry("Syllables", 28);
	kapp->quit();
}

/** Hide and show the MenuBar */
void KLettres::slotMenubar()
{
	switch (m_action->isChecked()){
		case false:
			m_action->setChecked(false);
			menuBar()->hide();
			tb->insertButton ("menubar.png", 3, SIGNAL( clicked() ), this, SLOT( slotShowM()), true, i18n("Show the MenuBar") );
		break;
		case true:
			m_action->setChecked(true);
			menuBar()->show();
			tb->removeItem(3);
		break;
		}
}

/** Hide and Show the ToolBar */
void KLettres::slotToolbar()
{
	switch (t_action->isChecked()){
		case false:
			t_action->setChecked(false);
			toolBar()->hide();
			resize(QSize( 640, 500 ));
			break;
		case true:
			t_action->setChecked(true);
			toolBar()->show();
			resize( QSize( 640, 538 ) );
		break;
		}
}

/** switch between different looks */
void KLettres::changeLook(int id)
{
	updateLookMenu(id);
    switch (id) {
        case 0:
            slotGrownup();
            break;
        case 1:
            slotKid();
            break;
    }
}

/** Set the Grown-up style */
void KLettres::slotGrownup()
{
	style="grownup";
	 setMinimumSize( QSize( 640, 525 ) );
    setMaximumSize( QSize( 640, 525 ) );
	//button1 background
	cg.setColor( QColorGroup::Foreground, white );
    cg.setColor( QColorGroup::Background, QColor(53,87,158));
    pal.setActive( cg );
    button1->setPalette( pal );

	look_menu->setCurrentItem(0);
	setBackgroundPixmap(pm_a);
	QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Background, white);
    pal.setActive( cg );
    statusBar()->setPalette( pal );
	menuBar()->show();
	m_action->setChecked(true);
	tb->insertCombo(lang_list, 2, false, SIGNAL( activated(int) ), this, SLOT( changeNumeration(int)), true, i18n("Change language"), 50);
	tb->setCurrentComboItem(2, num);
	tb->setEnableContextMenu(false);
	tb->setIconSize(22);
	int i = tb->count();
	if (i>4)
	{
		tb->removeItem(5);
		tb->removeItem(3);
	}

	tb->insertButton ("kids.png", 4, SIGNAL( clicked() ), this, SLOT( slotKid()), true, i18n("Switch to the kid look") );
	if (t_action->isChecked()==false)
	{
     		t_action->setChecked(true);
			toolBar()->show();
			setMinimumSize( QSize( 640, 525 ) );
    		setMaximumSize( QSize( 640, 525) );
			//resize( QSize( 640, 560 ) );
	}
	tb->enableMoving(false);
}

/** Set the kid style */
void KLettres::slotKid()
{
    style="kid";
    setMinimumSize( QSize( 640, 538 ) );
    setMaximumSize( QSize( 640, 538 ) );
	//change button1 background
	cg.setColor( QColorGroup::Foreground, white );
	cg.setColor( QColorGroup::Background, black);
    pal.setActive( cg );
    button1->setPalette( pal );

	look_menu->setCurrentItem(1);
	setBackgroundPixmap(pm_k);
	QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Background, white);
    pal.setActive( cg );
    statusBar()->setPalette( pal );
	menuBar()->hide();   //and insert show_menubar button
	int i = tb->count();
	if (i<6)
	tb->insertButton ("menubar.png", 3, SIGNAL( clicked() ), this, SLOT( slotShowM()), true, i18n("Show the MenuBar") );
	m_action->setChecked(false);
	tb->removeItem(2);
	tb->removeItem(4);//remove kid_look button
//button to show grown-up style
    tb->insertButton ("grownup.png", 5, SIGNAL( clicked() ), this, SLOT( slotGrownup()), true, i18n("Switch to the grown-up look") );
	 tb->setIconSize(32);
	 if (t_action->isChecked()==false)
	 {
     		t_action->setChecked(true);
			toolBar()->show();
			setMinimumSize( QSize( 640, 538 ) );
          setMaximumSize( QSize( 640, 538) );
	 }
	tb->enableMoving(false);
}


/** No descriptions */
void KLettres::slotShowM()
{
	m_action->setChecked(true);
	menuBar()->show();
	tb->removeItem(3);//remove menubar_button
}

#include "klettres.moc"






