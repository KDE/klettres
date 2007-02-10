
########### next target ###############

set(klettres_SRCS 
   klettres.cpp 
   klnewstuff.cpp 
   main.cpp 
   klettresview.cpp 
   soundfactory.cpp 
   langutils.cpp
   timer.cpp )

kde4_automoc(${klettres_SRCS})

kde4_add_ui_files(klettres_SRCS
    timerui.ui
    fontsdlg.ui )

kde4_add_kcfg_files(klettres_SRCS prefs.kcfgc )

kde4_add_executable(klettres ${klettres_SRCS})

target_link_libraries(klettres  ${KDE4_KDEUI_LIBS} ${KDE4_KNEWSTUFF_LIBS} ${KDE4_PHONONCORE_LIBRARY} )

install(TARGETS klettres  DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES klettres.desktop  DESTINATION  ${XDG_APPS_DIR} )
install( FILES klettresui.rc  DESTINATION  ${DATA_INSTALL_DIR}/klettres )
install( FILES klettres.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES klettresrc  DESTINATION  ${CONFIG_INSTALL_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR}   )
