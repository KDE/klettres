/*
 * Copyright (C) 2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#ifndef _KLETTRESVIEW_H_
#define _KLETTRESVIEW_H_

//Qt includes
#include <qaccel.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qwidget.h>
#include <qstring.h>
#include <qfile.h>
//KDE includes
#include <kaccelgen.h>
#include <kaction.h>
#include <kapplication.h>
#include <kcombobox.h>
#include <khelpmenu.h>
#include <klineedit.h>
#include <kmessagebox.h>
#include <kstandarddirs.h>


class KLettresView : public QWidget
{
    Q_OBJECT
public:
	/**
	 * Default constructor
	 */
    KLettresView(QWidget *parent);

	/**
	 * Destructor
	 */
    virtual ~KLettresView();

	QLabel* button1;
    QLineEdit* line1;

	QPixmap pm_k;
	QPixmap pm_a;

	QPalette pal;
    QColorGroup cg;

	QString s[30], sd[30], a1, t1, sb, s1, sj, st;
	QString langLoc;
	int l, l1, l2, n, niveau, num, temp;
	int length, input;
	QString string1, string2, dataString;
	QString style;
	QFile lev1File;


signals:

  	void newText( const QString& );



public slots:

	void slotGrownup();
	void slotKid();

	void game();
	void treat1(const QString& );
	void timer1();
	void slotLet2(const QString& );
	void timerDone();
	void play();
	void slotChooseSound();
};

#endif // _KLETTRESVIEW_H_
