####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = klettres
klettres_SOURCES = khsplash.cpp klettresdlg.ui klettres.cpp main.cpp 
klettres_LDADD   =  $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)

SUBDIRS = pics sons sons2

EXTRA_DIST = main.cpp klettres.cpp klettres.h klettres.desktop lo32-app-klettres.png lo16-app-klettres.png klettresdlg.ui khsplash.cpp khsplash.h level1.txt level3.txt 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Edutainment/French/
	$(INSTALL_DATA) $(srcdir)/klettres.desktop $(kde_appsdir)/Edutainment/French/klettres.desktop
#	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
#	$(INSTALL_DATA) $(srcdir)/lo32-app-klettres.png $(kde_icondir)/locolor/32x32/apps/klettres.png
#	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
#	$(INSTALL_DATA) $(srcdir)/lo16-app-klettres.png $(kde_icondir)/locolor/16x16/apps/klettres.png
	$(mkinstalldirs) $(kde_datadir)/klettres/
	$(INSTALL_DATA) $(srcdir)/level1.txt $(kde_datadir)/klettres/level1.txt
	$(mkinstalldirs) $(kde_datadir)/klettres/
	$(INSTALL_DATA) $(srcdir)/level3.txt $(kde_datadir)/klettres/level3.txt

uninstall-local:
	-rm -f $(kde_appsdir)/Edutainment/Frenchklettres.desktop
#	-rm -f $(kde_icondir)/locolor/32x32/apps/klettres.png
#	-rm -f $(kde_icondir)/locolor/16x16/apps/klettres.png
	-rm -f $(kde_datadir)/klettres/level1.txt
	-rm -f $(kde_datadir)/klettres/level3.txt

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
KDE_ICON=AUTO
METASOURCES = AUTO

# the library search path. 
klettres_LDFLAGS = $(all_libraries) $(KDE_RPATH)

messages: rc.cpp
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/klettres.pot; \
	fi

