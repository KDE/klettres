/***************************************************************************
 *   Copyright (C) 2005 by Michael Goettsche                               *
 *   michael.goettsche@kdemail.net         
 *   Copyright (C) 2006 by Anne-Marie Mahfouf                              *
 *   annma@kde.org                                 *
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

#include <klocale.h>

#include <tqlabel.h>
#include <tqslider.h>

#include "timer.h"
#include "prefs.h"


Timer::Timer()
    :timerdlg()
{
    timeGrownLabel->setText(TQString::number(Prefs::grownTimer()) + " " + i18n("tenths of second"));
    timeKidLabel->setText(TQString::number(Prefs::kidTimer()) + " " + i18n("tenths of second"));
    connect(kcfg_GrownTimer, TQT_SIGNAL(valueChanged(int)), this, TQT_SLOT(sliderValueChanged()));
    connect(kcfg_KidTimer, TQT_SIGNAL(valueChanged(int)), this, TQT_SLOT(sliderValueChanged()));
}


void Timer::sliderValueChanged()
{
    timeKidLabel->setText(TQString::number(kcfg_KidTimer->value()) + " " + i18n("tenths of second"));
    timeGrownLabel->setText(TQString::number(kcfg_GrownTimer->value()) + " " + i18n("tenths of second"));
}


#include "timer.moc"
