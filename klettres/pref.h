/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#ifndef _KLETTRESPREF_H_
#define _KLETTRESPREF_H_

#include <kdialogbase.h>
#include <qfont.h>
#include <qframe.h>
#include <qstring.h>

#include "pref2ui.h"

class KLettresPrefPageOne;
class KLettresPrefPageTwo;

class KLettresPreferences : public KDialogBase
{
    Q_OBJECT
public:
    //!constructor
    KLettresPreferences();
    //!the current font
    QFont newFont;
    //!holds the current language
    QString langString;
    //! holds kid or grownup to define background style
    QString style;
    int niveau;
    bool configChanged;

private:
    KLettresPrefPageOne *m_pageOne;
    KLettresPrefPageTwo *m_pageTwo;

private slots:
        ///load settings from configuration file
	void loadSettings();
	void slotOk();
	void slotApply();
	void slotCancel();
	void slotDefault();
	void slotSet();
	void slotChanged();
	///this slot is called when the user selects a new font
	void slotSetNewFont(const QFont &);
	///this slot is called when the user selects a new language
	void slotLang(int);

signals:
      	void aClicked();

};


class KLettresPrefPageOne : public QFrame
{
    Q_OBJECT
public:
    KLettresPrefPageOne(QWidget *parent = 0);

    QFont newFont;
    KFontChooser *fdlg;
};


class KLettresPrefPageTwo : public pref2ui
{
    Q_OBJECT
public:
    KLettresPrefPageTwo(QWidget *parent = 0);

private slots:

};

#endif // _KLETTRESPREF_H_
