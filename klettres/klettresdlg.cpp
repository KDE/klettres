#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './klettresdlg.ui'
**
** Created: Fri Mar 2 16:51:58 2001
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "klettresdlg.h"

#include <kcombobox.h>
#include <klineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qvariant.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/* 
 *  Constructs a KLettresDlg which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f' 
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
KLettresDlg::KLettresDlg( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "KLettresDlg" );
    resize( 608, 530 ); 
    setCaption( i18n( "KLettres - v0.1" ) );
    KLettresDlgLayout = new QGridLayout( this ); 
    KLettresDlgLayout->setSpacing( 6 );
    KLettresDlgLayout->setMargin( 11 );

    Layout1 = new QHBoxLayout; 
    Layout1->setSpacing( 6 );
    Layout1->setMargin( 0 );
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer );

    lab1 = new QLabel( this, "lab1" );
    lab1->setMinimumSize( QSize( 460, 110 ) );
    lab1->setMaximumSize( QSize( 460, 110 ) );
    QPalette pal;
    QColorGroup cg;
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 214, 205, 187) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 234, 230, 221) );
    cg.setColor( QColorGroup::Dark, QColor( 107, 103, 94) );
    cg.setColor( QColorGroup::Mid, QColor( 142, 136, 124) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, QColor( 233, 223, 204) );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 205, 123, 214) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 128, 0, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 214, 205, 187) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 246, 236, 215) );
    cg.setColor( QColorGroup::Dark, QColor( 107, 103, 94) );
    cg.setColor( QColorGroup::Mid, QColor( 142, 136, 124) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, QColor( 233, 223, 204) );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 205, 123, 214) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 128, 0, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 214, 205, 187) );
    cg.setColor( QColorGroup::Light, white );
    cg.setColor( QColorGroup::Midlight, QColor( 246, 236, 215) );
    cg.setColor( QColorGroup::Dark, QColor( 107, 103, 94) );
    cg.setColor( QColorGroup::Mid, QColor( 142, 136, 124) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, QColor( 233, 223, 204) );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 205, 123, 214) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 128, 0, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setDisabled( cg );
    lab1->setPalette( pal );
    QFont lab1_font(  lab1->font() );
    lab1_font.setFamily( "adobe-courier" );
    lab1_font.setPointSize( 28 );
    lab1_font.setBold( TRUE );
    lab1->setFont( lab1_font ); 
    lab1->setFrameShape( QLabel::Box );
    lab1->setFrameShadow( QLabel::Raised );
    lab1->setLineWidth( 2 );
    lab1->setText( i18n( "Listen and type the letter" ) );
    lab1->setAlignment( int( QLabel::AlignCenter ) );
    Layout1->addWidget( lab1 );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout1->addItem( spacer_2 );

    KLettresDlgLayout->addLayout( Layout1, 0, 0 );

    Layout2 = new QHBoxLayout; 
    Layout2->setSpacing( 6 );
    Layout2->setMargin( 0 );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout2->addItem( spacer_3 );

    button1 = new QPushButton( this, "button1" );
    button1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, button1->sizePolicy().hasHeightForWidth() ) );
    button1->setMinimumSize( QSize( 160, 170 ) );
    button1->setMaximumSize( QSize( 160, 170 ) );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 255, 232, 57) );
    cg.setColor( QColorGroup::Light, QColor( 255, 247, 184) );
    cg.setColor( QColorGroup::Midlight, QColor( 255, 239, 120) );
    cg.setColor( QColorGroup::Dark, QColor( 127, 115, 28) );
    cg.setColor( QColorGroup::Mid, QColor( 170, 155, 38) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, QColor( 233, 223, 204) );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 214, 205, 187) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 128, 0, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setActive( cg );
    cg.setColor( QColorGroup::Foreground, black );
    cg.setColor( QColorGroup::Button, QColor( 255, 232, 57) );
    cg.setColor( QColorGroup::Light, QColor( 255, 247, 184) );
    cg.setColor( QColorGroup::Midlight, QColor( 255, 236, 95) );
    cg.setColor( QColorGroup::Dark, QColor( 127, 115, 28) );
    cg.setColor( QColorGroup::Mid, QColor( 170, 155, 38) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, QColor( 233, 223, 204) );
    cg.setColor( QColorGroup::ButtonText, black );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 214, 205, 187) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 128, 0, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setInactive( cg );
    cg.setColor( QColorGroup::Foreground, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Button, QColor( 255, 232, 57) );
    cg.setColor( QColorGroup::Light, QColor( 255, 247, 184) );
    cg.setColor( QColorGroup::Midlight, QColor( 255, 236, 95) );
    cg.setColor( QColorGroup::Dark, QColor( 127, 115, 28) );
    cg.setColor( QColorGroup::Mid, QColor( 170, 155, 38) );
    cg.setColor( QColorGroup::Text, black );
    cg.setColor( QColorGroup::BrightText, QColor( 233, 223, 204) );
    cg.setColor( QColorGroup::ButtonText, QColor( 128, 128, 128) );
    cg.setColor( QColorGroup::Base, white );
    cg.setColor( QColorGroup::Background, QColor( 214, 205, 187) );
    cg.setColor( QColorGroup::Shadow, black );
    cg.setColor( QColorGroup::Highlight, QColor( 128, 0, 0) );
    cg.setColor( QColorGroup::HighlightedText, white );
    pal.setDisabled( cg );
    button1->setPalette( pal );
    QFont button1_font(  button1->font() );
    button1_font.setFamily( "bitstream-courier" );
    button1_font.setPointSize( 140 );
    button1_font.setBold( TRUE );
    button1->setFont( button1_font ); 
    button1->setText( i18n( "A" ) );
    Layout2->addWidget( button1 );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout2->addItem( spacer_4 );

    KLettresDlgLayout->addLayout( Layout2, 1, 0 );

    Layout5 = new QHBoxLayout; 
    Layout5->setSpacing( 6 );
    Layout5->setMargin( 0 );
    QSpacerItem* spacer_5 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout5->addItem( spacer_5 );

    line1 = new KLineEdit( this, "line1" );
    line1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, line1->sizePolicy().hasHeightForWidth() ) );
    line1->setMinimumSize( QSize( 160, 170 ) );
    line1->setMaximumSize( QSize( 160, 170 ) );
    QFont line1_font(  line1->font() );
    line1_font.setFamily( "bitstream-courier" );
    line1_font.setPointSize( 140 );
    line1_font.setBold( TRUE );
    line1->setFont( line1_font ); 
    line1->setCursor( QCursor( 0 ) );
    QToolTip::add(  line1, i18n( "Type the letter " ) );
    Layout5->addWidget( line1 );
    QSpacerItem* spacer_6 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout5->addItem( spacer_6 );

    KLettresDlgLayout->addLayout( Layout5, 2, 0 );

    Layout7 = new QHBoxLayout; 
    Layout7->setSpacing( 6 );
    Layout7->setMargin( 0 );

    aide = new QPushButton( this, "help" );
    aide->setMinimumSize( QSize( 100, 30 ) );
    QFont aide_font(  aide->font() );
    aide_font.setPointSize( 14 );
    aide_font.setBold( TRUE );
    aide->setFont( aide_font ); 
    aide->setText( i18n( "&Help" ) );
    aide->setAccel( 276824129 );
    QToolTip::add(  aide, i18n( "Call the help file" ) );
    Layout7->addWidget( aide );

    comb1 = new KComboBox( FALSE, this, "comb1" );
    comb1->insertItem( i18n( "Level 1" ) );
    comb1->insertItem( i18n( "Level 2" ) );
    comb1->insertItem( i18n( "Level 3" ) );
    comb1->insertItem( i18n( "Level 4" ) );
    comb1->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, comb1->sizePolicy().hasHeightForWidth() ) );
    comb1->setMinimumSize( QSize( 110, 30 ) );
    comb1->setMaximumSize( QSize( 110, 30 ) );
    QFont comb1_font(  comb1->font() );
    comb1_font.setPointSize( 14 );
    comb1_font.setBold( TRUE );
    comb1->setFont( comb1_font ); 
    QToolTip::add(  comb1, i18n( "Allow you to change level" ) );
    Layout7->addWidget( comb1 );
    QSpacerItem* spacer_7 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout7->addItem( spacer_7 );

    quitte = new QPushButton( this, "quit" );
    quitte->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)3, (QSizePolicy::SizeType)0, quitte->sizePolicy().hasHeightForWidth() ) );
    quitte->setMinimumSize( QSize( 100, 30 ) );
    quitte->setMaximumSize( QSize( 110, 30 ) );
    QFont quitte_font(  quitte->font() );
    quitte_font.setPointSize( 14 );
    quitte_font.setBold( TRUE );
    quitte->setFont( quitte_font ); 
    quitte->setText( i18n( "&Quit" ) );
    QToolTip::add(  quitte, i18n( "Quit the game" ) );
    Layout7->addWidget( quitte );

    KLettresDlgLayout->addLayout( Layout7, 3, 0 );

    // signals and slots connections
    connect( aide, SIGNAL( clicked() ), this, SLOT( slotAide() ) );
    connect( comb1, SIGNAL( activated(int) ), this, SLOT( slotNext(int) ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
KLettresDlg::~KLettresDlg()
{
    // no need to delete child widgets, Qt does it all for us
}

/*  
 *  Main event handler. Reimplemented to handle application
 *  font changes
 */
bool KLettresDlg::event( QEvent* ev )
{
    bool ret = QDialog::event( ev ); 
    if ( ev->type() == QEvent::ApplicationFontChange ) {
	QFont lab1_font(  lab1->font() );
	lab1_font.setFamily( "adobe-courier" );
	lab1_font.setPointSize( 28 );
	lab1_font.setBold( TRUE );
	lab1->setFont( lab1_font ); 
	QFont button1_font(  button1->font() );
	button1_font.setFamily( "bitstream-courier" );
	button1_font.setPointSize( 140 );
	button1_font.setBold( TRUE );
	button1->setFont( button1_font ); 
	QFont line1_font(  line1->font() );
	line1_font.setFamily( "bitstream-courier" );
	line1_font.setPointSize( 140 );
	line1_font.setBold( TRUE );
	line1->setFont( line1_font ); 
	QFont aide_font(  aide->font() );
	aide_font.setPointSize( 14 );
	aide_font.setBold( TRUE );
	aide->setFont( aide_font ); 
	QFont comb1_font(  comb1->font() );
	comb1_font.setPointSize( 14 );
	comb1_font.setBold( TRUE );
	comb1->setFont( comb1_font ); 
	QFont quitte_font(  quitte->font() );
	quitte_font.setPointSize( 14 );
	quitte_font.setBold( TRUE );
	quitte->setFont( quitte_font ); 
    }
    return ret;
}

void KLettresDlg::slotAide()
{
    qWarning( "KLettresDlg::slotAide(): Not implemented yet!" );
}

void KLettresDlg::slotLet2(const QString&)
{
    qWarning( "KLettresDlg::slotLet2(const QString&): Not implemented yet!" );
}

void KLettresDlg::slotNext(int)
{
    qWarning( "KLettresDlg::slotNext(int): Not implemented yet!" );
}

#include "klettresdlg.moc"
