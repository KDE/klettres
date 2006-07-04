

add_subdirectory(langs)

########### install files ###############

install( FILES sounds.xml  DESTINATION  ${DATA_INSTALL_DIR}/klettres/data )




#original Makefile.am contents follow:

#SUBDIRS = $(AUTODIRS)
#xml_DATA = sounds.xml
#xmldir = $(kde_datadir)/klettres/data
#
#
#
