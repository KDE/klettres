/***************************************************************************
 *   Copyright (C) 2001-2008 by Anne-Marie Mahfouf                              *
 *   annma@kde.org                                             *
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

#include <QLineEdit>

class QPixmap;
class QRect;
class QSvgRenderer;
class KLettres;
class KLTheme;

/**
 * This class serves as the view for KLettres.  It holds the GUI for the kid and grown-up looks
 * and has the code to display the letter/syllable and play the sound.
 *
 * @short KLettres View class
 * @author Anne-Marie Mahfouf <annma@kde.org>
 * @version 2.1
 */


class KLettresView : public QWidget
{
    Q_OBJECT
public:
    /**
     * Default constructor
     */
    explicit KLettresView(KLettres *parent);

    /**
     * Destructor
     */
    virtual ~KLettresView();
    /// Enter a letter into the input widget.
    void  enterLetter(const QString &letter) { m_letterEdit->setText(letter); }

    ///The timer value i.e. the time for displaying the letters/syllables
    int m_timer;
    ///The index to the random sequence
    int randomInt;
    ///A Klettres object
    KLettres *m_klettres;
    ///The line where the user enters his/her input
    QLineEdit *m_letterEdit;
    ///set the chosen theme
    void setTheme(KLTheme *theme);

protected:

    ///If the user hits backpace
    void keyReleaseEvent(QKeyEvent * e) Q_DECL_OVERRIDE;
    ///Cursor position in the line edit
    int m_cursorPos;
    ///Random number that decides on the letter/syllable and sound
    int m_random;
    ///Length of the syllables
    int m_length;
    ///Choose a sound in random and ensure that it's not the same than the previous one
    void chooseSound();
    ///Current letter or syllable stored
    QString m_currentLetter;
    ///Current letter entered uppercase i.e. m_inputLetter.upper()
    QString m_upperLetter;
    ///Paint the letter/syllable in levels 1 and 3 and the background
    void paintEvent( QPaintEvent * ) Q_DECL_OVERRIDE;
    ///Paint the background picture
    void paintBackground(QPainter &p, const QRect& rect);    
    ///Paint the letter/syllable in levels 1 and 3 
    void paintLetter(QPainter &p, const QRect& rect);
    ///Current theme
    KLTheme *m_theme = nullptr;

    // Graphics  ----------------
    QSvgRenderer *m_renderer = nullptr;
    QPixmap       m_backgroundCache;

public Q_SLOTS:
    ///Start playing displaying a new letter/syllable, playing the associated sound
    void game();

public Q_SLOTS:
    ///Play the same sound again
    void slotPlayAgain();

    void slotProcess(const QString &inputLetter);

    void slotTimerDone();

};

#endif // KLETTRESVIEW_H
