/*
    SPDX-FileCopyrightText: 2005 Michael Goettsche
    michael.goettsche@kdemail.net
    SPDX-FileCopyrightText: 2006 Anne-Marie Mahfouf
    annemarie.mahfouf@free.fr

    SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef TIMER_H_
#define TIMER_H_

#include <QWidget>
#include "ui_timerui.h"

/**
 * @short Timer widget in Settings dialog
 * @author Michael Goettsche <michael.goettsche@kdemail.net >
 * @version 0.1
 */

class Timer : public QWidget
{
Q_OBJECT

public:
     ///Constructor
    Timer();

protected:
    Ui::timerui ui_timer;

protected Q_SLOTS:
    ///When the QSlider value changes
    void sliderValueChanged();
};


#endif //TIMER_H_
