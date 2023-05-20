/*
    SPDX-FileCopyrightText: 2001-2008 Anne-Marie Mahfouf <annma@kde.org>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

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
    ~KLettresView() override;
    /// Enter a letter into the input widget.
    void  enterLetter(const QString &letter) { m_letterEdit->setText(letter); }

    ///The timer value i.e. the time for displaying the letters/syllables
    int m_timer;
    ///The index to the random sequence
    int randomInt;
    ///A Klettres object
    KLettres *m_klettres = nullptr;
    ///The line where the user enters his/her input
    QLineEdit *m_letterEdit = nullptr;
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
