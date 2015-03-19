
########### next target ###############

add_definitions(-DTRANSLATION_DOMAIN=\"kletters\")

set(klettres_SRCS
   klettres.cpp
   main.cpp
   klettresview.cpp
   soundfactory.cpp
   langutils.cpp
   kltheme.cpp
   timer.cpp
   klettres_debug.cpp )


ki18n_wrap_ui(klettres_SRCS
    timerui.ui
    fontsdlg.ui )

kconfig_add_kcfg_files(klettres_SRCS prefs.kcfgc )

#kde4_add_app_icon(klettres_SRCS "${KDE4_ICON_DIR}/oxygen/*/apps/klettres.png")
#kde4_add_app_icon(klettres_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/ox*-apps-klettres.png")
file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*-apps-klettres.png")
ecm_add_app_icon(klettres_SRCS ICONS ${ICONS_SRCS})

add_executable(klettres ${klettres_SRCS})

target_link_libraries(klettres
  KF5::Completion
  KF5::Emoticons
  KF5::NewStuff
  KF5::I18n
  KF5::ItemModels
  KF5::KDELibs4Support
  Qt5::Svg
  ${PHONON_LIBRARY}
  Qt5::Xml)

install(TARGETS klettres  ${INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS org.kde.klettres.desktop  DESTINATION  ${XDG_APPS_INSTALL_DIR} )
install( FILES klettresui.rc  DESTINATION  ${KXMLGUI_INSTALL_DIR}/klettres )
install( FILES klettres.kcfg  DESTINATION  ${KCFG_INSTALL_DIR} )
install( FILES klettres.knsrc  DESTINATION  ${CONFIG_INSTALL_DIR} )

ecm_install_icons( ICONS 128-apps-klettres.png  16-apps-klettres.png  22-apps-klettres.png  32-apps-klettres.png  48-apps-klettres.png  64-apps-klettres.png DESTINATION ${ICON_INSTALL_DIR}   )
