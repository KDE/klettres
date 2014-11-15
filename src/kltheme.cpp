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

#include <KLocalizedString>

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
        return i18nc("@item:inlistbox", "Kid");
    }

    virtual QString svgFileName() const
    {
        return "klettres_kids.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(215, 215, 215); 
    }

    virtual QColor backgroundInputColor() const
    {
        return QColor(187, 76, 58); 
    }

    virtual QColor letterInputColor() const
    {
        return QColor(215, 215, 215); 
    }

    virtual QRect wordRect(const QSize& windowsize) const
    {
        return QRect(windowsize.width()*200/800, windowsize.height()*200/600, 250, 160);
    }

    virtual QRect inputRect(const QSize& windowsize) const
    {
        return QRect(windowsize.width()*188/800, windowsize.height()*468/600, 25, 90);
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
        return i18nc("@item:inlistbox desert theme for the interface", "Desert");
    }

    virtual QString svgFileName() const
    {
        return "klettres_desert.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(115, 50, 95); 
    }

    virtual QColor backgroundInputColor() const
    {
        return QColor(202, 217, 84); 
    }

    virtual QColor letterInputColor() const
    {
        return QColor(141, 80, 17); 
    }

    virtual QRect wordRect(const QSize& windowsize) const
    {
	return QRect(windowsize.width()*230/800, windowsize.height()*140/600, 250, 160);
    }

    virtual QRect inputRect(const QSize& windowsize) const
    {
        return QRect(windowsize.width()*380/800, windowsize.height()*480/600, 250, 160);
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
        return i18nc("@item:inlistbox", "Savannah");
    }

    virtual QString svgFileName() const
    {
        return "klettres_savannah.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(215, 215, 215); 
    }

    virtual QColor backgroundInputColor() const
    {
        return QColor(196, 189, 94); 
    }

    virtual QColor letterInputColor() const
    {
        return QColor(141, 80, 17); 
    }

    virtual QRect wordRect(const QSize& windowsize) const
    {
        return QRect(windowsize.width()*230/800, windowsize.height()*80/600, 250, 160);
    }

    virtual QRect inputRect(const QSize& windowsize) const
    {
        return QRect(windowsize.width()*540/800, windowsize.height()*480/600, 250, 160);
    }
};

///The 'Aqua' theme

class KLThemeAqua : public KLTheme
{
public:
    KLThemeAqua()
        : KLTheme()
    {
    }

    virtual QString name() const
    {
        return "aqua";
    }

    virtual QString uiName() const
    {
        return i18nc("@item:inlistbox", "Aqua");
    }

    virtual QString svgFileName() const
    {
        return "klettres_aqua.svg";
    }

    virtual QColor letterColor() const
    {
        return QColor(215, 215, 215); 
    }

    virtual QColor backgroundInputColor() const
    {
        return QColor(0, 0, 100); 
    }

    virtual QColor letterInputColor() const
    {
        return QColor(0, 0, 215); 
    }

    virtual QRect wordRect(const QSize& windowsize) const
    {
        return QRect(windowsize.width()*150/800, windowsize.height()*180/600, 250, 160);
    }

    virtual QRect inputRect(const QSize& windowsize) const
    {
	return QRect(windowsize.width()*600/800, windowsize.height()*480/600, 250, 160);
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
	case 3:
	    return new KLThemeAqua();
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
    ADD_THEME_NAME( KLThemeAqua, ret)
    return ret;
}




