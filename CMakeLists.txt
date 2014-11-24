project(klettres)

#minimum requirements
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.2.0")

# we need some parts of the ECM CMake helpers
find_package (ECM 1.3.0 REQUIRED NO_MODULE)
set (CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
include(ECMOptionalAddSubdirectory)
include(CMakePackageConfigHelpers)
include(ECMInstallIcons)

include(KDEInstallDirs)
include(KDECompilerSettings)
include(KDECMakeSettings)
include(ECMAddTests)

# Load the frameworks we need

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED
  Core
  Svg
  Test
  Widgets
)
find_package(Phonon4Qt5)

find_package(KF5 REQUIRED COMPONENTS
  Completion
  DocTools
  Emoticons
  ItemModels
  I18n
  KDELibs4Support
  NewStuff
  WidgetsAddons
  ConfigWidgets
  CoreAddons
)

include(KDE4Defaults)

include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${PHONON_INCLUDE_DIR})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)

ecm_optional_add_subdirectory( doc )
ecm_optional_add_subdirectory( src )
ecm_optional_add_subdirectory( pics )
ecm_optional_add_subdirectory( data )
ecm_optional_add_subdirectory( sounds )
ecm_optional_add_subdirectory( icons )
ecm_optional_add_subdirectory( themes )
ecm_optional_add_subdirectory( tests )
