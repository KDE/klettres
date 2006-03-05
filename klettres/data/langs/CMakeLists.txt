kde4_header()

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}  )


########### install files ###############

install_files( ${DATA_INSTALL_DIR}/klettres FILES cs.txt da.txt sk.txt es.txt )

kde4_footer()



#original Makefile.am contents follow:

#txt_DATA=cs.txt da.txt sk.txt es.txt
#txtdir=$(kde_datadir)/klettres