
add_subdirectory( pics ) 
add_subdirectory( data ) 
add_subdirectory( icons ) 




########### next target ###############

set(klettres_SRCS 
   klettres.cpp 
   klnewstuff.cpp 
   main.cpp 
   klettresview.cpp 
   soundfactory.cpp 
   timer.cpp )

kde4_automoc(${klettres_SRCS})

kde4_add_ui3_files(klettres_SRCS fontsdlg.ui  )
kde4_add_ui_files(klettres_SRCS timerui.ui )

kde4_add_kcfg_files(klettres_SRCS prefs.kcfgc )

kde4_add_executable(klettres ${klettres_SRCS})

target_link_libraries(klettres  ${KDE4_KDEUI_LIBS} knewstuff ${KDE4_PHONONCORE_LIBS} )

install_targets(/bin klettres )


########### install files ###############

install_files( ${XDG_APPS_DIR} FILES klettres.desktop )
install_files( ${DATA_INSTALL_DIR}/klettres FILES klettresui.rc )
install_files( ${KCFG_INSTALL_DIR} FILES klettres.kcfg )
install_files( ${DATA_INSTALL_DIR}/klettres/en FILES en/sounds.xml )
install_files( ${CONFIG_INSTALL_DIR} FILES klettresrc )
install_files( ${DATA_INSTALL_DIR}/klettres/fr FILES fr/sounds.xml )

kde4_install_icons( ${ICON_INSTALL_DIR}  hicolor )




#original Makefile.am contents follow:

######## kdevelop will overwrite this part!!! (begin)##########
#bin_PROGRAMS = klettres
#
### INCLUDES were found outside kdevelop specific part
#
#klettres_SOURCES = fontsdlg.ui klettres.cpp klnewstuff.cpp main.cpp klettresview.cpp soundfactory.cpp prefs.kcfgc timerui.ui timer.cpp
#klettres_LDADD   = $(LIB_KDEUI) -lknewstuff
#
#SUBDIRS = pics data icons
#
#xdg_apps_DATA = klettres.desktop
#kde_kcfg_DATA = klettres.kcfg
#kde_conf_DATA = klettresrc
#
#appdir = $(kde_datadir)/klettres
#app_DATA = klettresui.rc
#
######## kdevelop will overwrite this part!!! (end)############
## set the include path for X, qt and KDE
#INCLUDES= $(all_includes)
#
#METASOURCES = AUTO
#
#KDE_ICON = AUTO
#
## the library search path.
#klettres_LDFLAGS = $(all_libraries) $(KDE_RPATH)
#
#messages: rc.cpp
#	$(XGETTEXT) *.cpp -o $(podir)/klettres.pot;
#
#LANGS = fr en
#SUBS = alpha syllab
#
#xmlen_DATA = en/sounds.xml
#xmlendir = $(kde_datadir)/klettres/en
#
#xmlfr_DATA = fr/sounds.xml
#xmlfrdir = $(kde_datadir)/klettres/fr
#
#install-data-local:
#	@for lang in $(LANGS); do \
#		for sub in $(SUBS); do \
#		   $(mkinstalldirs) $(DESTDIR)$(kde_datadir)/klettres/$$lang/$$sub ;\
#		   list=`cd $(srcdir)/$$lang/$$sub && ls -1d *` ;\
#		   for file in $$list; do \
#			if test -f $(srcdir)/$$lang/$$sub/$$file; then \
#			    echo $(INSTALL_DATA) $(srcdir)/$$lang/$$sub/$$file $(DESTDIR)$(kde_datadir)/klettres/$$lang/$$sub/$$file ;\
#			    $(INSTALL_DATA) $(srcdir)/$$lang/$$sub/$$file $(DESTDIR)$(kde_datadir)/klettres/$$lang/$$sub/$$file ;\
#			fi ;\
#		   done ;\
#		done ;\
#	done
#
#uninstall-local:
#	for lang in $(LANGS); do \
#		rm -rf $(DESTDIR)$(kde_datadir)/klettres/$$lang ;\
#	done
#
