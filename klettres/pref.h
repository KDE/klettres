/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#ifndef _KLETTRESPREF_H_
#define _KLETTRESPREF_H_

#include <kdialogbase.h>
#include <qfont.h>
#include <qframe.h>
#include <qstring.h>

#include "pref1ui.h"
#include "pref2ui.h"

class KLettresPrefPageOne;
class KLettresPrefPageTwo;
class KLettresPrefPageThree;

class KLettresPreferences : public KDialogBase
{
    Q_OBJECT
public:
    KLettresPreferences();

    QFont newFont;
    QString langString;
    QString style;//kid or grownup
    int niveau;
    bool configChanged;

private:
    KLettresPrefPageOne *m_pageOne;
    KLettresPrefPageTwo *m_pageTwo;
    KLettresPrefPageThree *m_pageThree;

private slots:
	void readConfig();
	void writeConfig();
	void slotOk();
	void slotApply();
	void slotCancel();
	void slotDefault();
	void slotSet();
	void slotChanged();
	void slotChangeLevel(int);
	void slotChangeLook(int);
	void slotSetNewFont(const QFont &);
	void slotLang(int);

signals:
      	void aClicked();
	void fClicked();
};

class KLettresPrefPageOne : public pref1ui
{
    Q_OBJECT
public:
    KLettresPrefPageOne(QWidget *parent = 0);

private slots:

};

class KLettresPrefPageTwo : public QFrame
{
    Q_OBJECT
public:
    KLettresPrefPageTwo(QWidget *parent = 0);

    QFont newFont;
    KFontChooser *fdlg;
};

class KLettresPrefPageThree : public pref2ui
{
    Q_OBJECT
public:
    KLettresPrefPageThree(QWidget *parent = 0);

private slots:

};

#endif // _KLETTRESPREF_H_
