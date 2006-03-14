kde4_header()

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}  )
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
