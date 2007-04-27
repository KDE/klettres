/***************************************************************************
 *   Copyright (C) 2001-2007 by Anne-Marie Mahfouf                              *
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

#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QSvgRenderer>
#include <QFile>
#include <QPaintEvent>

#include <klocale.h>
#include <kstandarddirs.h>
#include <kdebug.h>
//Project headers
#include "klettres.h"
#include "klettresview.h"
#include "prefs.h"
#include "kltheme.h"

KLettresView::KLettresView(KLettres *parent)
        : QWidget(parent)
{
    m_klettres = parent;

    //lineEdit for user input
    m_letterEdit = new KLineEdit( this );
    m_letterEdit->setToolTip(i18n("Type the letter or syllable that you just heard" ) );
    m_letterEdit->setFont(Prefs::font());
    m_letterEdit->setAutoFillBackground(true);

    randomInt          = 0;
    m_theme            = 0; // essential
    m_renderer = new QSvgRenderer();
    setTheme(KLThemeFactory::instance()->buildTheme(0));
}

KLettresView::~KLettresView()
{
    delete m_renderer;
    delete m_theme;
}

void KLettresView::chooseSound()
{
    //get the next random sound
    m_random=m_klettres->soundFactory->randomList[randomInt%m_klettres->soundFactory->sounds];
    //The sound is played
    kDebug() << "m_random " << m_random << endl;
    m_klettres->soundFactory->playSound(m_random);
    //store letter or syllable in m_currentLetter
    m_currentLetter = m_klettres->soundFactory->namesList[m_random];
    //Find the length of the syllable
    m_length=m_klettres->soundFactory->namesList[m_random].length();
    kDebug() << "syllable length " << m_length << endl;
    int width;
    if (m_length<3)
        width = 200;
    else
        width = 200+(20*(m_length-2));
    m_letterEdit->setMinimumSize( QSize( width, 100 ) );
    m_letterEdit->setMaximumSize( QSize( width, 100 ) );
    update();
}

void KLettresView::setTheme(KLTheme *theme)
{
    // we don't allow null themes
    if (!theme)
        return;

    QString svgpath = KStandardDirs::locate("data", QString("klettres/pics/%1/%2").arg(theme->name(), theme->svgFileName()));

    // we don't allow themes with no svg installed
    if (!QFile::exists(svgpath))
        return;

    delete m_theme;
    m_theme = theme;

    // stylesheet   
    int r1, g1, b1;
    m_theme->backgroundInputColor().getRgb(&r1, &g1, &b1);
    int r2, g2, b2;
    m_theme->letterInputColor().getRgb(&r2, &g2, &b2);
    m_letterEdit->setStyleSheet(QString("border-style: solid; background-color: rgb(%1, %2, %3); color: rgb(%4, %5, %6) ; border-color: rgb(%4, %5, %6); border-bottom-right-radius:10; border-radius: 15px; border-width: 3px").arg(r1).arg(g1).arg(b1).arg(r2).arg(g2).arg(b2));

    m_renderer->load(svgpath);
    m_backgroundCache = QPixmap();
    update();
}

void KLettresView::paintEvent( QPaintEvent * e )
{
    QPainter p(this);
    paintBackground(p, e->rect());
    paintLetter(p, e->rect());
}

void KLettresView::paintBackground(QPainter &p, const QRect& rect)
{
    // Draw the background
    if (m_backgroundCache.size() != size()) {
        m_backgroundCache = QPixmap(size());
        QPainter aux(&m_backgroundCache);
        m_renderer->render(&aux);
    }
     p.drawPixmap(rect.topLeft(), m_backgroundCache, rect);
}

void KLettresView::paintLetter(QPainter &p, const QRect& rect)
{
    if (Prefs::level()%2==1) {
    QRect myRect = m_theme->wordRect(size());
    if (!myRect.intersects(rect))
        return;

    p.setPen( m_theme->letterColor());
    p.setFont(Prefs::font());
    p.drawText(myRect, m_currentLetter);
    }
    m_letterEdit->setGeometry( m_theme->inputRect(size()));  
    m_letterEdit->setFocus();
}

void KLettresView::game()
{
    m_cursorPos =1;
    //reset everything so when you change language or levels
    //it all restarts nicely
    QObject::disconnect(m_letterEdit, SIGNAL(textChanged(const QString&)),this,SLOT(slotProcess(const QString&)) );
    m_letterEdit->clear();
    m_letterEdit->setCursorPosition(0);
    m_letterEdit->setFocus();
    chooseSound();
    randomInt++;
    QObject::connect(m_letterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotProcess(const QString&)) );
}

void KLettresView::slotProcess(const QString &inputLetter)
{
    QObject::disconnect(m_letterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotProcess(const QString&)) );
    kDebug() << "Input: " << inputLetter << endl;
    m_inputLetter=m_letterEdit->text();
    if (m_inputLetter.at(0).isLetter()) //(a1.at(inputLetter.length()).lower().isLetter())
    {
        m_upperLetter = m_inputLetter.toUpper();    //put it in uppercase
        m_letterEdit->selectAll();
        m_letterEdit->cut();
        m_letterEdit->setText(m_upperLetter);
        QTimer *timer = new QTimer( this );
        connect( timer, SIGNAL(timeout()), this, SLOT(slotTimerDone()) );
        timer->setSingleShot(true);
        timer->start( m_timer*100);
    }
    else if (m_inputLetter.length() < m_cursorPos)
    {
        kDebug() << "In backspace case !!! " << endl;
        m_cursorPos--;
        QObject::connect(m_letterEdit, SIGNAL(textChanged(const QString&)),this,SLOT(slotProcess(const QString&)) );
    }
    else
    {
        kDebug() << "in no char loop" << endl;
        kDebug() << "cursor " << m_cursorPos << endl;
        m_letterEdit->backspace();
        QObject::connect(m_letterEdit, SIGNAL(textChanged(const QString&)),this,SLOT(slotProcess(const QString&)) );
    }
}

void KLettresView::slotTimerDone()
{
    kDebug() << "in timer done" << endl;
    QString match = m_currentLetter.left(m_cursorPos );
    if (match == m_upperLetter)
    {
        if (m_cursorPos!=m_length)  //if text in lineEdit not equal to text on button
        {            //i.e if you still have to allow input
            m_letterEdit->setMaxLength( m_cursorPos +1 );
            m_letterEdit->setCursorPosition( m_cursorPos );
            m_letterEdit->setFocus();
            m_cursorPos ++;
            QObject::connect(m_letterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotProcess(const QString&)) );
        }
        else
        {
            m_letterEdit->selectAll();
            m_letterEdit->cut();
            m_letterEdit->setCursorPosition(0 );
            m_letterEdit->setFocus();
            m_letterEdit->setMaxLength( 1 );
            game();  //another syllable
        }
    }
    else   //if not, cut it
    {
        m_letterEdit->backspace();  //delete the char to the left  and position curseur accordingly
        m_letterEdit->setFocus();
        //play sound again
        m_klettres->soundFactory->playSound(m_random);

        QObject::connect(m_letterEdit, SIGNAL(textChanged(const QString&)), this, SLOT(slotProcess(const QString&)) );
    }
}

void KLettresView::slotPlayAgain()
{
    //TODO wait for the previous sound to be payed before playing again as it won't play if the previous one was not finished
    m_klettres->soundFactory->playSound(m_random);
}

#include "klettresview.moc"
