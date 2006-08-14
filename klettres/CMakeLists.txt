
remove_definitions(-DQT3_SUPPORT_WARNINGS)
remove_definitions(-DQT3_SUPPORT)

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

kde4_add_ui_files(klettres_SRCS
    timerui.ui
    fontsdlg.ui )

kde4_add_kcfg_files(klettres_SRCS prefs.kcfgc )

kde4_add_executable(klettres ${klettres_SRCS})

target_link_libraries(klettres  ${KDE4_KDEUI_LIBS} knewstuff ${KDE4_PHONONCORE_LIBRARY} )

install(TARGETS klettres  DESTINATION ${BIN_INSTALL_DIR} )


########### install files ###############

install( FILES klettres.desktop  DESTINATION  ${XDG_APPS_DIR} )
install( FILES klettresui.rc  DESTINATION  ${DATA_INSTALL_DIR}/klettres )
install( FILES klettres.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES klettresrc  DESTINATION  ${CONFIG_INSTALL_DIR} )

kde4_install_icons( ${ICON_INSTALL_DIR}   )

set(langdir fr en )
set(sublangdir alpha syllab )
foreach (_langcurrentdir ${langdir})
	FILE(GLOB _xmlfile "${_langcurrentdir}/*.xml" )
	install(FILES ${_xmlfile} DESTINATION ${DATA_INSTALL_DIR}/klettres/${_langcurrentdir})
	foreach(_sublangcurrentdir ${sublangdir})
		FILE(GLOB _oggfile "${_langcurrentdir}/${_sublangcurrentdir}/*.ogg" )
		install(FILES ${_oggfile} DESTINATION ${DATA_INSTALL_DIR}/klettres/${_langcurrentdir}/${_sublangcurrentdir})
	endforeach(_sublangcurrentdir ${sublangdir} )
endforeach(_langcurrentdir ${langdir})

