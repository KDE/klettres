/****************************************************************************
** Form interface generated from reading ui file './klettresdlg.ui'
**
** Created: Fri Mar 2 16:51:29 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef KLETTRESDLG_H
#define KLETTRESDLG_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class KComboBox;
class KLineEdit;
class QLabel;
class QPushButton;

class KLettresDlg : public QDialog
{ 
    Q_OBJECT

public:
    KLettresDlg( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~KLettresDlg();

    QLabel* lab1;
    QPushButton* button1;
    KLineEdit* line1;
    QPushButton* aide;
    KComboBox* comb1;
    QPushButton* quitte;

public slots:
    virtual void slotAide();
    virtual void slotLet2(const QString&);
    virtual void slotNext(int);

protected:
    QGridLayout* KLettresDlgLayout;
    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QHBoxLayout* Layout5;
    QHBoxLayout* Layout7;
    bool event( QEvent* );
};

#endif // KLETTRESDLG_H
