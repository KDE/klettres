#!/usr/bin/env ruby
#
# This script gets all KLettres data currently in trunk/l10n-kde4 svn and makes
# tarballs of it, removing svn hidden dirs and CMakeLists.txt
#
# (c) 2005 Mark Kretschmann <markey@web.de>
# (c) 2007 - 2008 Anne-Marie Mahfouf <annma@kde.org>
# modified by Carsten Niehaus
# Some parts of this code taken from cvs2dist
# License: GPL V2+

# Each tarball is packaged klettres-<iso>.tar.bz2 where <iso> is the language
# iso code used by KDE

# Globally these tarballs should be unpacked under
# $KDEDIRS/share/apps/klettres
# Locally, these tarballs should be unpacked under
# $KDEHOME/share/apps/klettres

puts "Connecting to l10n-kde4".center(40, " - ")

Dir.mkdir( "klettres-data")
Dir.chdir( "klettres-data" )

i18nlangs = `svn cat svn://anonsvn.kde.org/home/kde/trunk/l10n-kde4/subdirs`

# docs
for lang in i18nlangs
	print "doing #{lang}";
	lang.chomp!
	datadirname = "l10n-kde4/#{lang}/data/kdeedu/klettres"
	Dir.mkdir( "#{lang}" )
	Dir.chdir( "#{lang}" )
        `svn co -q svn://anonsvn.kde.org/home/kde/trunk/#{datadirname}`
	Dir.chdir( ".." )
	if !FileTest.exists?( "#{lang}/klettres" )
   		print "in if \n" 
   		Dir.rmdir("#{lang}")
	else
		system `mv #{lang}/klettres/* #{lang}`
		system `rm -Rf #{lang}/klettres/.*`
		system `rmdir #{lang}/klettres`
		system `rm #{lang}/CMakeLists.txt`
	    	system `rm #{lang}/alpha/CMakeLists.txt`
   		system `rm -Rf #{lang}/alpha/.svn`
	    	system `rm #{lang}/syllab/CMakeLists.txt`
   		system `rm -Rf #{lang}/syllab/.svn`
	end
end

Dir.foreach('.') { |dir|
	next if dir == "."
	next if dir == ".."
	`tar -cf klettres-#{dir}.tar #{dir}/`
	`bzip2 klettres-#{dir}.tar`
	system `rm -Rf #{dir}/`
}
