/*
    This file is part of KOrganizer.
    Copyright (c) 2002 Cornelius Schumacher <schumacher@kde.org>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

    As a special exception, permission is given to link this program
    with any edition of Qt, and distribute the resulting executable,
    without including the source code for Qt in the source distribution.
*/

#include <kapplication.h>
#include <kdebug.h>
#include <kconfig.h>
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
