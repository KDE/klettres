/*
 * Copyright (C) 2001-2003 Anne-Marie Mahfouf <annma@kde.org>
 */

#ifndef _KLETTRESPREF_H_
#define _KLETTRESPREF_H_


class KLettresPrefPageOne;

class KLettresPreferences : public KDialogBase
{
    Q_OBJECT
public:
    ///Constructor
    KLettresPreferences();
    ///The current font
    QFont newFont;
    ///true if settings have changed
    bool configChanged;
private:
    KLettresPrefPageOne *m_pageOne;


private slots:

	///Read settings in config file
	void loadSettings();
        ///When the Ok button is clicked, settings are written in config and dialog closes
	void slotOk();
        ///When Apply button is clicked, then it's disabled
	void slotApply();
	void slotCancel();
	void slotDefault();
	void slotChanged();
	void slotSetNewFont(const QFont &);

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

#endif // _KLETTRESPREF_H_