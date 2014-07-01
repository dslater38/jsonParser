find_path(CPPUNIT_INCLUDE_DIR cppunit/TestRunner.h)
find_library(CPPUNIT_LIBRARY cppunit)

add_executable(ut.json valuetest.cc testmain.cc)
include_directories(${CPPUNIT_INCLUDE_DIR})
target_link_libraries(ut.json json ${CPPUNIT_LIBRARY})
