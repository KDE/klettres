/*
 * Copyright (c) 2002 Cornelius Schumacher <schumacher@kde.org>
 * Copyright (C) 2001-2004 Anne-Marie Mahfouf <annma@kde.org>
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
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
    */

#include <kdebug.h>
#include <ktar.h>
#include <qdir.h>
#include <kaction.h>
#include "klnewstuff.h"

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
    QStringList mdirs = KGlobal::dirs()->findDirs("data", "klettres");
    QStringList foundLanguages="";
    for (QStringList::Iterator it =mdirs.begin(); it !=mdirs.end(); ++it ) {
        QDir dir(*it);
        foundLanguages += dir.entryList(QDir::Dirs, QDir::Name);
        foundLanguages.remove(foundLanguages.find("."));
        foundLanguages.remove(foundLanguages.find(".."));
    }
    foundLanguages.remove(foundLanguages.find("data"));
    foundLanguages.remove(foundLanguages.find("pics"));
    foundLanguages.remove(foundLanguages.find(""));
    //look for the new installed language: is in foundLanguages and not in m_languages
    bool enabled;
    QString tmp;
    for (uint i=0;  i<foundLanguages.count(); i++)
    {
        if (m_view->klettres->m_languages.grep(foundLanguages[i]).isEmpty())
            tmp = foundLanguages[i];
    }
    enabled = locate("data", "klettres/"+ tmp+"/") != 0;
    //add the new language in the menu
    if (enabled)
        m_view->klettres->registerLanguage(tmp,"");
    m_view->klettres->m_languageAction->setItems(m_view->klettres->m_languageNames);
    m_view->klettres->m_languageAction->setCurrentItem(m_view->klettres->selectedLanguage);
    return true;
}

bool KLNewStuff::createUploadFile( const QString &fileName )
{
    //return mView->saveCalendar( fileName );
    return true;
}
