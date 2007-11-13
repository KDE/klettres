
########### next target ###############

set(klettres_SRCS 
   klettres.cpp 
   main.cpp 
   klettresview.cpp 
   soundfactory.cpp 
   langutils.cpp
   kltheme.cpp
   timer.cpp )


kde4_add_ui_files(klettres_SRCS
    timerui.ui
    fontsdlg.ui )

kde4_add_kcfg_files(klettres_SRCS prefs.kcfgc )

set(klettres_icons
    ${CMAKE_INSTALL_PREFIX}/share/icons/oxygen/16x16/apps/klettres.png
    ${CMAKE_INSTALL_PREFIX}/share/icons/oxygen/32x32/apps/klettres.png
    ${CMAKE_INSTALL_PREFIX}/share/icons/oxygen/48x48/apps/klettres.png
    ${CMAKE_INSTALL_PREFIX}/share/icons/oxygen/64x64/apps/klettres.png
    ${CMAKE_INSTALL_PREFIX}/share/icons/oxygen/128x128/apps/klettres.png
)
kde4_add_win32_app_icon(klettres_SRCS ${klettres_icons})
kde4_add_executable(klettres ${klettres_SRCS})

target_link_libraries(klettres  ${KDE4_KNEWSTUFF2_LIBS} ${KDE4_PHONON_LIBS} )

install(TARGETS klettres  DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES klettres.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES klettresui.rc  DESTINATION  ${DATA_INSTALL_DIR}/klettres )
install( FILES klettres.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES klettres.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR}   )
