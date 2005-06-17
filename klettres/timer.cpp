/***************************************************************************
 *   Copyright (C) 2005 by Michael Goettsche                               *
 *   michael.goettsche@kdemail.net                                         *
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
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <klocale.h>

#include <qlabel.h>
#include <qslider.h>

#include "timer.h"
#include "prefs.h"


Timer::Timer()
    :timerdlg()
{
    timeGrownLabel->setText(QString::number(Prefs::grownTimer()) + " " + i18n("seconds"));
    timeKidLabel->setText(QString::number(Prefs::kidTimer()) + " " + i18n("seconds"));
    connect(kcfg_GrownTimer, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged()));
    connect(kcfg_KidTimer, SIGNAL(valueChanged(int)), this, SLOT(sliderValueChanged()));
}


void Timer::sliderValueChanged()
{
    timeKidLabel->setText(QString::number(kcfg_KidTimer->value()) + " " + i18n("seconds"));
    timeGrownLabel->setText(QString::number(kcfg_GrownTimer->value()) + " " + i18n("seconds"));
}


#include "timer.moc"
