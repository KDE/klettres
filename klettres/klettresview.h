/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>

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

#ifndef _KLETTRESVIEW_H_
#define _KLETTRESVIEW_H_

//Qt includes
#include <qlabel.h>
//KDE includes
#include <kapplication.h>
#include <klineedit.h>
#include <kstandarddirs.h>

class QDomDocument;
class KLettres;

class KLettresView : public QWidget
{
    Q_OBJECT
public:
	/**
	 * Default constructor
	 */
    	KLettresView(KLettres *parent);

	/**
	 * Destructor
	 */
    	virtual ~KLettresView();

        ///The button that display the letter or syllable
	QLabel* button1;
        ///The line where the user enters his/her input
        QLineEdit* line1;
	///The pixmap for the kid background
	QPixmap pm_k;
        ///The pixmap for the grown-up background
	QPixmap pm_a;
	///Palette changes wether it's kid or grown-up
	QPalette pal;
        QColorGroup cg;
	///Current level
        int niveau;
        ///Random number that decides on the letter/syllable and sound
        int n;
        ///Temporary number to store the previous random and check that it's not twice the same
        int  temp;
        ///Length of the syllables
        int length;
        ///Number corresponding to the selected language: 0 is Czech, 1 is Danish, 2 is French (default), 3 is Dutch
        uint selectedLanguage;
        ///Current style (kid or grownup)
        QString style;
        ///Current letter or syllable stored
        QString st;
        ///Current input in line1
        QString sj;
	///User input in upper case
        QString t1;
        ///User input
        QString a1;
	///Cursor position in the line edit
        int input;

public slots:
	///Set the Grown-up background, show menubar, show the Kid button
	void slotGrownup();
	///Set the Kid background pic, hide the menubar, show the Grownup button
	void slotKid();
	/**This begin the game or begin a new level: set button and lineedit sizes
	 * set connections
	 */
	void game();
	void treat1(const QString& );
	void timer1();
	void slotLet2(const QString& );
	void timerDone();
	///Choose a sound in random and ensure that it's not the same than the previous one
	void chooseSound();

private:

	KLettres *klettres;

};

#endif // _KLETTRESVIEW_H_
