/***************************************************************************
 *   Copyright (C) 2005 by Michael Goettsche                               *
 *   michael.goettsche@kdemail.net                                         *
 *   Copyright (C) 2006 by Anne-Marie Mahfouf                               *
 *   annemarie.mahfouf@free.fr   *
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
