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

#ifndef KLETTRESVIEW_H
#define KLETTRESVIEW_H

#include <tqwidget.h>
#include <tqpalette.h>
#include <klineedit.h>

class TQLabel;
class KLettres;

/**
 * This class serves as the view for KLettres.  It holds the GUI for the kid and grown-up looks
 * and has the code to display the letter/syllable and play the sound.
 *
 * @short KLettres View class
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 1.1
 */


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

    ///Set the Grown-up background, show menubar, show the Kid button
    void viewThemeArctic();
    ///Set the Kid background pic, hide the menubar, show the Grownup button
    void viewThemeClassroom();
    ///Set the Desert background pic, hide the menubar, show the Grownup button
    void viewThemeDesert();
    ///The timer value i.e. the time for displaying the letters/syllables
    int m_timer;
    ///A Klettres object
    KLettres *m_klettres;
    ///The line where the user enters his/her input
    KLineEdit *m_letterEdit;

protected:

    ///The pixmaps for the themes backgrounds
    TQPixmap m_grownupPicture,
    m_kidPicture,
    m_desertPicture;
    ///Palette changes wether it's kid or grown-up
    TQPalette pal;
    TQColorGroup cg;
    ///cursor position in the line edit
    int m_cursorPos;
    ///Random number that decides on the letter/syllable and sound
    int m_random;
    ///Length of the syllables
    int m_length;
    ///Choose a sound in random and ensure that it's not the same than the previous one
    void chooseSound();
    ///Current letter or syllable stored
    TQString m_currentLetter;
    ///Current letter entered uppercase i.e. m_inputLetter.upper()
    TQString m_upperLetter;
    ///Current letter entered
    //TQString m_inputLetter; NOTE: not used
    ///Paint the letter/syllable in levels 1 and 3
    void paintEvent( TQPaintEvent * );

    public slots:
    ///Start playing displaying a new letter/syllable, playing the associated sound
    void game();

    protected slots:
    ///Play the same sound again
    void slotPlayAgain();
    
    void slotProcess(const TQString &inputLetter);

    void slotTimerDone();
};

#endif // KLETTRESVIEW_H
