#minimum requirements
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# KDE Application Version, managed by release script
set(RELEASE_SERVICE_VERSION_MAJOR "21")
set(RELEASE_SERVICE_VERSION_MINOR "07")
set(RELEASE_SERVICE_VERSION_MICRO "90")
set(RELEASE_SERVICE_VERSION "${RELEASE_SERVICE_VERSION_MAJOR}.${RELEASE_SERVICE_VERSION_MINOR}.${RELEASE_SERVICE_VERSION_MICRO}")

project(klettres VERSION ${RELEASE_SERVICE_VERSION})

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.83.0")


# we need some parts of the ECM CMake helpers
find_package (ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
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

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
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

ki18n_install(po)
if (KF5DocTools_FOUND)
    kdoctools_install(po)
endif()
install(FILES org.kde.klettres.appdata.xml DESTINATION ${KDE_INSTALL_METAINFODIR})


ecm_qt_install_logging_categories(EXPORT KLETTRES FILE klettres.categories DESTINATION ${KDE_INSTALL_LOGGINGCATEGORIESDIR})

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


