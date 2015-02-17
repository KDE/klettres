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

#include "timer.h"


#include <KLocalizedString>

#include "prefs.h"

Timer::Timer()
    :QWidget()
{
    ui_timer.setupUi(this);
    ui_timer.timeGrownLabel->setText(i18np("1 tenth of second", "%1 tenths of second", Prefs::grownTimer()));
    ui_timer.timeKidLabel->setText(i18np("1 tenth of second", "%1 tenths of second", Prefs::kidTimer()));
    connect(ui_timer.kcfg_GrownTimer, &QSlider::valueChanged, this, &Timer::sliderValueChanged);
    connect(ui_timer.kcfg_KidTimer, &QSlider::valueChanged, this, &Timer::sliderValueChanged);
}


void Timer::sliderValueChanged()
{
    ui_timer.timeKidLabel->setText(i18np("1 tenth of second", "%1 tenths of second", ui_timer.kcfg_KidTimer->value()));
    ui_timer.timeGrownLabel->setText(i18np("1 tenth of second", "%1 tenths of second", ui_timer.kcfg_GrownTimer->value()));
}



