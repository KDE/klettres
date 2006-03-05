kde4_header()

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}  )


########### install files ###############

install_files( ${DATA_INSTALL_DIR}/klettres/pics FILES klettres_kids.jpeg klettres_grownup.png klettres_desert.png )

kde4_footer()



#original Makefile.am contents follow:

#pics_DATA = klettres_kids.jpeg klettres_grownup.png klettres_desert.png
#picsdir = $(kde_datadir)/klettres/pics
