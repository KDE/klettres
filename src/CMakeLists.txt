
########### next target ###############

ecm_setup_version(${RELEASE_SERVICE_VERSION} VARIABLE_PREFIX KLETTRES VERSION_HEADER klettres_version.h)

set(klettres_SRCS
    klettres.cpp
    klettres.h
    klettresview.cpp
    klettresview.h
    kltheme.cpp
    kltheme.h
    langutils.cpp
    langutils.h
    main.cpp
    soundfactory.cpp
    soundfactory.h
    timer.cpp
    timer.h
    klettres.qrc
    )

ecm_qt_declare_logging_category(klettres_SRCS HEADER klettres_debug.h IDENTIFIER KLETTRES_LOG CATEGORY_NAME log_klettres DESCRIPTION "klettres" EXPORT KLETTRES)

ki18n_wrap_ui(klettres_SRCS
    timerui.ui
    fontsdlg.ui )

kconfig_add_kcfg_files(klettres_SRCS prefs.kcfgc )

file(GLOB ICONS_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*-apps-klettres.png")
ecm_add_app_icon(klettres_SRCS ICONS ${ICONS_SRCS})

add_executable(klettres ${klettres_SRCS})

target_link_libraries(klettres
  KF6::Crash
  KF6::NewStuffWidgets
  KF6::I18n
  KF6::XmlGui
  Qt::Multimedia
  Qt::Svg
  Qt::Xml)

install(TARGETS klettres  ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} )


########### install files ###############

install( PROGRAMS org.kde.klettres.desktop  DESTINATION  ${KDE_INSTALL_APPDIR} )
install( FILES klettres.kcfg  DESTINATION  ${KDE_INSTALL_KCFGDIR} )
install( FILES klettres.knsrc  DESTINATION  ${KDE_INSTALL_KNSRCDIR} )

ecm_install_icons( ICONS 128-apps-klettres.png  16-apps-klettres.png  22-apps-klettres.png  32-apps-klettres.png  48-apps-klettres.png  64-apps-klettres.png DESTINATION ${KDE_INSTALL_ICONDIR}   )
