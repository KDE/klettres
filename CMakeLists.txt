#minimum requirements
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# KDE Application Version, managed by release script
set(KDE_APPLICATIONS_VERSION_MAJOR "19")
set(KDE_APPLICATIONS_VERSION_MINOR "07")
set(KDE_APPLICATIONS_VERSION_MICRO "80")
set(KDE_APPLICATIONS_VERSION "${KDE_APPLICATIONS_VERSION_MAJOR}.${KDE_APPLICATIONS_VERSION_MINOR}.${KDE_APPLICATIONS_VERSION_MICRO}")

project(klettres VERSION ${KDE_APPLICATIONS_VERSION})

set(QT_MIN_VERSION "5.2.0")

# we need some parts of the ECM CMake helpers
find_package (ECM 1.7.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMOptionalAddSubdirectory)
include(CMakePackageConfigHelpers)
include(ECMInstallIcons)

include(KDEInstallDirs)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings)
include(ECMAddTests)
include(ECMAddAppIcon)
include(ECMQtDeclareLoggingCategory)
include(ECMSetupVersion)

# Load the frameworks we need

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
  Core
  Svg
  Network
  Test
  Widgets
)
find_package(Phonon4Qt5 REQUIRED)

find_package(KF5 REQUIRED COMPONENTS
  Completion
  Crash
  DocTools
  I18n
  NewStuff
  WidgetsAddons
  ConfigWidgets
  CoreAddons
)

include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${PHONON_INCLUDE_DIR})

ecm_optional_add_subdirectory( doc )
ecm_optional_add_subdirectory( src )
ecm_optional_add_subdirectory( pics )
ecm_optional_add_subdirectory( data )
ecm_optional_add_subdirectory( sounds )
ecm_optional_add_subdirectory( icons )
ecm_optional_add_subdirectory( themes )
ecm_optional_add_subdirectory( tests )

install(FILES org.kde.klettres.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})

if (${ECM_VERSION} STRGREATER "5.58.0")
    install(FILES klettres.categories  DESTINATION  ${KDE_INSTALL_LOGGINGCATEGORIESDIR})
else()
    install(FILES klettres.categories  DESTINATION ${KDE_INSTALL_CONFDIR})
endif()


feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


