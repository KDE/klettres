####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = klettres
klettres_SOURCES = khsplash.cpp klettresdlg.cpp klettres.cpp main.cpp 
klettres_LDADD   =  $(LIB_KDEUI) 

SUBDIRS = sons sons2 

KDE_ICON = klettres

level_DATA = level1.txt level3.txt
leveldir = $(kde_datadir)/klettres

pics_DATA = klettres-main.png klettres-main2.png
picsdir = $(kde_datadir)/klettres/pics

apps_DATA = klettres.desktop
appsdir = $(kde_appsdir)/Edutainment/French

sound_DATA = splash2.mp3
sounddir = $(kde_datadir)/klettres/sounds

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
klettres_LDFLAGS = $(all_libraries) $(KDE_RPATH)

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/klettres.pot; \
	fi

