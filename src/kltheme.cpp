/***************************************************************************
 *   Copyright (C) Copyright (C) 2007      Pino Toscano <pino@kde.org>                                            *
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

//project headers
#include "kltheme.h"

#include <klocale.h>

KLTheme::KLTheme()
{
}

KLTheme::~KLTheme()
{
}

/// The 'kids' theme
class KLThemeKid : public KLTheme
{
public:
    KLThemeKid()
        : KLTheme()
    {
    }

    virtual QString name() const
    {
        return "kids";
    }

    virtual QString uiName() const
    {
        return i18n("Kid");
    }

    virtual QString svgFileName() const
    {
        return "klettres_kids.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(Qt::black); 
    }

};

/// The 'desert' theme
class KLThemeDesert : public KLTheme
{
public:
    KLThemeDesert()
        : KLTheme()
    {
    }

    virtual QString name() const
    {
        return "desert";
    }

    virtual QString uiName() const
    {
        return i18n("Desert");
    }

    virtual QString svgFileName() const
    {
        return "klettres_desert.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(115, 50, 95); //purple
    }

};

/// The 'savannah' theme
class KLThemeSavannah : public KLTheme
{
public:
    KLThemeSavannah()
        : KLTheme()
    {
    }

    virtual QString name() const
    {
        return "savannah";
    }

    virtual QString uiName() const
    {
        return i18n("Savannah");
    }

    virtual QString svgFileName() const
    {
        return "klettres_savannah.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(141, 80, 17); 
    }

};

KLThemeFactory* KLThemeFactory::instance()
{
    static KLThemeFactory factory;
    return &factory;
}

KLThemeFactory::KLThemeFactory()
{
}

KLThemeFactory::~KLThemeFactory()
{
}

KLTheme* KLThemeFactory::buildTheme(int id) const
{
    switch (id)
    {
        case 0:
            return new KLThemeKid();
	case 1:
            return new KLThemeDesert();
	case 2:
            return new KLThemeSavannah();
    }
    return 0;
}

#define ADD_THEME_NAME( themeclass, list ) \
{ \
   themeclass x; \
   list.append( x.uiName() ); \
}
QStringList KLThemeFactory::themeList() const
{
    QStringList ret;
    ADD_THEME_NAME( KLThemeKid, ret )
    ADD_THEME_NAME( KLThemeDesert, ret )
    ADD_THEME_NAME( KLThemeSavannah, ret )
    return ret;
}




