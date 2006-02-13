/*
 * Copyright (c) 2002 Cornelius Schumacher <schumacher@kde.org>
 * Copyright (C) 2004-2006 Anne-Marie Mahfouf <annma@kde.org>
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

#include <kdebug.h>
#include <ktar.h>
#include <qdir.h>
#include <kaction.h>
#include <kapplication.h>
#include <kstandarddirs.h>
#include "klnewstuff.h"
#include "prefs.h"

KLNewStuff::KLNewStuff( KLettresView *view ) :
        KNewStuff( "klettres", view ),
        m_view( view )
{
}

bool KLNewStuff::install( const QString &fileName )
{
    kdDebug(5850) << "KLNewStuff::install(): " << fileName << endl;

    KTar archive( fileName );
    if ( !archive.open( IO_ReadOnly ) )
        return false;
    const KArchiveDirectory *archiveDir = archive.directory();
    KStandardDirs myStdDir;
    const QString destDir =myStdDir.saveLocation("data", kapp->instanceName() + "/", true);
    KStandardDirs::makeDir( destDir );
    archiveDir->copyTo(destDir);
    archive.close();
    //look for languages dirs installed
    m_view->m_klettres->findLanguages();
    //refresh Languages menu
    //kdDebug() << "---- selected language : " << m_view->m_klettres->selectedLanguage << endl;
    m_view->m_klettres->m_languageAction->setItems(m_view->m_klettres->m_languageNames);
    m_view->m_klettres->slotChangeLanguage(m_view->m_klettres->m_languages.findIndex(Prefs::defaultLanguage()));
    m_view->m_klettres->m_languageAction->setCurrentItem(m_view->m_klettres->m_languages.findIndex(Prefs::defaultLanguage()));
    return true;
}

bool KLNewStuff::createUploadFile( const QString &fileName )
{
    //return mView->saveCalendar( fileName );
    return true;
}
