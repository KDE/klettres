set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR} )


set(malayalamtest_SOURCES malayalamtest.cpp)

kde4_add_unit_test(malayalamtest ${malayalamtest_SOURCES})

target_link_libraries(malayalamtest ${KDE4_KDECORE_LIBS}
${QT_QTTEST_LIBRARY})
