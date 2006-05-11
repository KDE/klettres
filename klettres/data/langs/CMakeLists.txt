kde4_header()




########### install files ###############

install_files( ${DATA_INSTALL_DIR}/klettres FILES cs.txt da.txt sk.txt es.txt )

kde4_footer()



#original Makefile.am contents follow:

#txt_DATA=cs.txt da.txt sk.txt es.txt
#txtdir=$(kde_datadir)/klettres