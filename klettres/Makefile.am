####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = klettres
klettres_SOURCES = khsplash.cpp klettresdlg.cpp klettres.cpp main.cpp 
klettres_LDADD   =  $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)

SUBDIRS = sons sons2 

EXTRA_DIST = main.cpp klettres.cpp klettres.h klettres.desktop lo32-app-klettres.png lo16-app-klettres.png klettresdlg.cpp klettresdlg.h level1.txt level3.txt khsplash.cpp khsplash.h klettres-main.png splash2.mp3 klettres-main2.png 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Edutainment/French/
	$(INSTALL_DATA) $(srcdir)/klettres.desktop $(kde_appsdir)/Edutainment/French/klettres.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/lo32-app-klettres.png $(kde_icondir)/locolor/32x32/apps/klettres.png
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-klettres.png $(kde_icondir)/locolor/16x16/apps/klettres.png
	$(mkinstalldirs) $(kde_datadir)/klettres/
	$(INSTALL_DATA) $(srcdir)/level1.txt $(kde_datadir)/klettres/level1.txt
	$(mkinstalldirs) $(kde_datadir)/klettres/
	$(INSTALL_DATA) $(srcdir)/level3.txt $(kde_datadir)/klettres/level3.txt
	$(mkinstalldirs) $(kde_datadir)/klettres/pics/
	$(INSTALL_DATA) $(srcdir)/klettres-main.png $(kde_datadir)/klettres/pics/klettres-main.png
	$(mkinstalldirs) $(kde_datadir)/klettres/sounds/
	$(INSTALL_DATA) $(srcdir)/splash2.mp3 $(kde_datadir)/klettres/sounds/splash2.mp3
	$(mkinstalldirs) $(kde_datadir)/klettres/pics/
	$(INSTALL_DATA) $(srcdir)/klettres-main2.png $(kde_datadir)/klettres/pics/klettres-main2.png

uninstall-local:
	-rm -f $(kde_appsdir)/Edutainment/French/klettres.desktop
	-rm -f $(kde_icondir)/locolor/32x32/apps/klettres.png
	-rm -f $(kde_icondir)/locolor/16x16/apps/klettres.png
	-rm -f $(kde_datadir)/klettres/level1.txt
	-rm -f $(kde_datadir)/klettres/level3.txt
	-rm -f $(kde_datadir)/klettres/pics/klettres-main.png
	-rm -f $(kde_datadir)/klettres/sounds/splash2.mp3
	-rm -f $(kde_datadir)/klettres/pics/klettres-main2.png

####### kdevelop will overwrite this part!!! (end)############
# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
klettres_LDFLAGS = $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE´s XML GUI builing
#rcdir = $(kde_datadir)/klettres
#rc_DATA = klettresui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/klettres.pot; \
	fi

