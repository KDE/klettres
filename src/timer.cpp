/*
    SPDX-FileCopyrightText: 2005 Michael Goettsche <michael.goettsche@kdemail.net>
    SPDX-FileCopyrightText: 2006 Anne-Marie Mahfouf <annemarie.mahfouf@free.fr>

    SPDX-License-Identifier: GPL-2.0-or-later
*/

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

#include "moc_timer.cpp"
