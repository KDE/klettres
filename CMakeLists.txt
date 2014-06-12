project(klettres)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)

include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${KDE4_INCLUDES} ${QT4_INCLUDES})
add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
add_subdirectory( doc )
add_subdirectory( src )

add_subdirectory( pics )
add_subdirectory( data )
add_subdirectory( sounds )
add_subdirectory( icons )
add_subdirectory( themes )
add_subdirectory( tests )

install(FILES klettres.appdata.xml DESTINATION ${SHARE_INSTALL_PREFIX}/appdata/)
