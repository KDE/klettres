####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = klettres

## INCLUDES were found outside kdevelop specific part

klettres_SOURCES = fontsdlg.ui klettres.cpp main.cpp klettresview.cpp soundfactory.cpp prefs.kcfgc
klettres_LDADD   = $(LIB_KDEUI)

SUBDIRS = pics data

xdg_apps_DATA = klettres.desktop
kde_kcfg_DATA = klettres.kcfg

appdir = $(kde_datadir)/klettres
app_DATA = klettresui.rc

####### kdevelop will overwrite this part!!! (end)############
# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# install all the standard icons
# added by bml
KDE_ICON = klettres

# the library search path.
klettres_LDFLAGS = $(all_libraries) $(KDE_RPATH)

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/klettres.pot;

LANGS = cs da fr nl sk
SUBS = alpha syllab

install-data-local:
	@for lang in $(LANGS); do \
		for sub in $(SUBS); do \
		   $(mkinstalldirs) $(DESTDIR)$(kde_datadir)/klettres/$$lang/$$sub ;\
		   list=`cd $(srcdir)/$$lang/$$sub && ls -1d *` ;\
		   for file in $$list; do \
			if test -f $(srcdir)/$$lang/$$sub/$$file; then \
			    echo $(INSTALL_DATA) $(srcdir)/$$lang/$$sub/$$file $(DESTDIR)$(kde_datadir)/klettres/$$lang/$$sub/$$file ;\
			    $(INSTALL_DATA) $(srcdir)/$$lang/$$sub/$$file $(DESTDIR)$(kde_datadir)/klettres/$$lang/$$sub/$$file ;\
			fi ;\
		   done ;\
		done ;\
	done

uninstall-local:
	for lang in $(LANGS); do \
		rm -rf $(DESTDIR)$(kde_datadir)/klettres/$$lang ;\
	done

