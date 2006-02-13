/*
 *  Copyright (c) 2002 Cornelius Schumacher <schumacher@kde.org>
 *  Copyright (C) 2004-2006 Anne-Marie Mahfouf <annma@kde.org>
 *
    This program is free software; you can redistribute it and/or
    modify it under the terms of version 2 of the GNU General Public
    License as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
    */

#ifndef KLNEWSTUFF_H
#define KLNEWSTUFF_H

#include "knewstuff/knewstuff.h"
#include "klettres.h"

class KLettres;

class KLNewStuff : public KNewStuff
{
public:
    KLNewStuff( KLettresView * );

    bool install( const QString &fileName );
    bool createUploadFile( const QString &fileName );

    //private:
    KLettresView *m_view;
};

#endif
