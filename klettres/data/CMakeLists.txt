kde4_header()


add_subdirectory(langs)

########### install files ###############

install_files( ${DATA_INSTALL_DIR}/klettres/data FILES sounds.xml )

kde4_footer()



#original Makefile.am contents follow:

#SUBDIRS = $(AUTODIRS)
#xml_DATA = sounds.xml
#xmldir = $(kde_datadir)/klettres/data
#
#
#
