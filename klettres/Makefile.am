####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = klettres

## INCLUDES were found outside kdevelop specific part

klettres_SOURCES = khsplash.cpp klettres.cpp main.cpp 
klettres_LDADD   =  $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)

SUBDIRS = pics French Dutch Danish

EXTRA_DIST = main.cpp klettres.cpp klettres.h klettres.desktop lo32-app-klettres.png lo16-app-klettres.png hi16-app-klettres.png hi32-app-klettres.png khsplash.cpp khsplash.h lo32-app-klettres.xcf klettresui.rc 

desktopdir = $(kde_appsdir)/Edutainment

desktop_DATA = klettres.desktop

appdir = $(kde_datadir)/klettres

app_DATA = klettresui.rc

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

# install all the standard icons
# added by bml
KDE_ICON = klettres

# the library search path. 
klettres_LDFLAGS = $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE
#rcdir = $(kde_datadir)/klettres
#rc_DATA = klettresui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/klettres.pot;

