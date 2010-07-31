/***************************************************************************
 *   Copyright (C) 2001-2006 by Anne-Marie Mahfouf                              *
 *   annemarie.mahfouf@free.fr                                             *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.             *
 ***************************************************************************/

#include <tqlabel.h>
#include <tqtimer.h>
#include <tqtooltip.h>
#include <tqwhatsthis.h>
#include <tqpainter.h>

#include <kapplication.h>
#include <klocale.h>
#include <kstandarddirs.h>
#include <kdebug.h>
//Project headers
#include "klettres.h"
#include "klettresview.h"
#include "prefs.h"

KLettresView::KLettresView(KLettres *parent)
        : TQWidget(parent)
{
    m_klettres = parent;

    setMinimumSize( TQSize( 640, 480 ) );
    setMaximumSize( TQSize( 640, 480 ) );

    //lineEdit for user input
    m_letterEdit = new KLineEdit( this, "line1" );
    m_letterEdit->setGeometry( TQRect( 40, 310, 161, 160 ) );
    TQToolTip::add( m_letterEdit, i18n( "Type the letter or syllable that you just heard" ) );

    setFont(Prefs::font());
    //load background pics
    m_grownupPicture.load(locate("data","klettres/pics/klettres_grownup.png"));
    m_kidPicture.load(locate("data","klettres/pics/klettres_kids.jpeg"));
    m_desertPicture.load(locate("data","klettres/pics/klettres_desert.png"));

}

KLettresView::~KLettresView()
{
}

void KLettresView::chooseSound()
{
    //If there are no sounds loaded
    if (m_klettres->soundFactory->sounds ==0)
        return;
    //get a random sound
    m_random=kapp->random()%(m_klettres->soundFactory->sounds);
    //have not 2 same sounds consecutively
    int temp = 0;
    if (temp<0)
        temp=m_random;
    else
    {
        while (m_random==temp)
            m_random=kapp->random()%(m_klettres->soundFactory->sounds);
        temp=m_random;
    }

    //The sound is played
    kdDebug() << "m_random " << m_random << endl;
    m_klettres->soundFactory->playSound(m_random);
    //store letter or syllable in m_currentLetter
    m_currentLetter = m_klettres->soundFactory->namesList[m_random];
    //Find the length of the syllable
    m_length=m_klettres->soundFactory->namesList[m_random].length();
    kdDebug() << "syllable length " << m_length << endl;
    int width;
    if (m_length<3)
        width = 200;
    else
        width = 200+(20*(m_length-2));
    update();
    m_letterEdit->setMinimumSize( TQSize( width, 160 ) );
    m_letterEdit->setMaximumSize( TQSize( width, 160 ) );
}

void KLettresView::paintEvent( TQPaintEvent * )
{
    if (Prefs::level()%2==1) {
        TQPainter paint(this);
        paint.setFont(Prefs::font());
        TQString start = i18n("Start");

        paint.setFont(Prefs::font());
        if (Prefs::theme() == Prefs::EnumTheme::desert) {
            paint.setPen( TQColor(115, 50, 95)); //brown
            //m_letterEdit->setPaletteForegroundColor(TQColor(115, 50, 95));
        }
        else if (Prefs::theme() == Prefs::EnumTheme::arctic) {
            paint.setPen( Qt::white );
            //m_letterEdit->setPaletteForegroundColor(TQColor(48, 75, 137));
        }
        else {
            paint.setPen( Qt::white );
            //m_letterEdit->setPaletteForegroundColor(Qt::black);
        }
        paint.drawText(50, 230, m_currentLetter);
    }
}


void KLettresView::game()
{
    m_cursorPos = 1;
    //reset everything so when you change language or levels
    //it all restarts nicely
    TQObject::disconnect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)),this,TQT_SLOT(slotProcess(const TQString&)) );
    m_letterEdit->clear();
    m_letterEdit->setCursorPosition(0);
    m_letterEdit->setMaxLength(1); //fix that's in trunk
    m_letterEdit->setFocus();
    chooseSound();
    TQObject::connect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)), this, TQT_SLOT(slotProcess(const TQString&)) );
}

void KLettresView::slotProcess(const TQString &inputLetter)
{
    TQObject::disconnect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)), this, TQT_SLOT(slotProcess(const TQString&)) );
    //check if backspace
    if(inputLetter.length() != m_cursorPos)
    {
        m_cursorPos--;
        m_letterEdit->setMaxLength( m_cursorPos );
        TQObject::connect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)),this,TQT_SLOT(slotProcess(const TQString&)) );
        return;
    }

    TQChar input_character = inputLetter.at(inputLetter.length()-1);

    if (input_character.isLetter()) //(a1.at(inputLetter.length()).lower().isLetter())
    {
        m_upperLetter = inputLetter.upper();    //put it in uppercase
        m_letterEdit->selectAll();
        m_letterEdit->cut();
        m_letterEdit->setText(m_upperLetter);
        TQTimer::singleShot(m_timer*100, this, TQT_SLOT(slotTimerDone()));
    }
    else
    {
        kdDebug() << "in no char loop" << endl;
        kdDebug() << "cursor " << m_cursorPos << endl;
        m_letterEdit->backspace();
        TQObject::connect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)),this,TQT_SLOT(slotProcess(const TQString&)) );
    }
}

void KLettresView::slotTimerDone()
{
    kdDebug() << "in timer done" << endl;
    TQString match = m_currentLetter.left(m_cursorPos );

    if (match == m_upperLetter)
    {
        if (m_cursorPos!=m_length)  //if text in lineEdit not equal to text on button
        {            //i.e if you still have to allow input
            m_letterEdit->setMaxLength( m_cursorPos +1 );
            m_letterEdit->setCursorPosition( m_cursorPos );
            m_letterEdit->setFocus();
            m_cursorPos ++;
            TQObject::connect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)), this, TQT_SLOT(slotProcess(const TQString&)) );
        }
        else
        {
            game();  //another syllable
        }
    }
    else   //if not, cut it
    {
        m_letterEdit->backspace();  //delete the char to the left  and position curseur accordingly
        m_letterEdit->setFocus();
        //play sound again
        m_klettres->soundFactory->playSound(m_random);

        TQObject::connect(m_letterEdit, TQT_SIGNAL(textChanged(const TQString&)), this, TQT_SLOT(slotProcess(const TQString&)) );
    }
}

void KLettresView::slotPlayAgain()
{
    //TODO wait for the previous sound to be payed before playing again as it won't play if the previous one was not finished
    m_klettres->soundFactory->playSound(m_random);
}

void KLettresView::viewThemeArctic()
{
    Prefs::setTheme(Prefs::EnumTheme::arctic);
    Prefs::writeConfig();
    setPaletteBackgroundPixmap(m_grownupPicture);
}

void KLettresView::viewThemeClassroom()
{
    Prefs::setTheme(Prefs::EnumTheme::classroom);
    Prefs::writeConfig();
    setPaletteBackgroundPixmap(m_kidPicture);
}

void KLettresView::viewThemeDesert()
{
    Prefs::setTheme(Prefs::EnumTheme::desert);
    Prefs::writeConfig();
    setPaletteBackgroundPixmap(m_desertPicture);
}

#include "klettresview.moc"
