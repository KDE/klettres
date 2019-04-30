include(ECMMarkAsTest)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})

set(malayalamtest_SRCS
  malayalamtest.cpp
)

add_executable(MalayalamTest ${malayalamtest_SRCS})
add_test(NAME MalayalamTest COMMAND MalayalamTest)
ecm_mark_as_test(MalayalamTest)
target_link_libraries(MalayalamTest
  Qt5::Test
)

