find_path(CPPUNIT_INCLUDE_DIR cppunit/TestRunner.h)
find_library(CPPUNIT_LIBRARY cppunit)

add_executable(
	ut.json

	ucs16toutf8test.cc
	unescapeescapecharactertest.cc
	unescapejsonescapecharactertest.cc
	unescapeunicodeescapesequencetest.cc
	valuetest.cc
	parsefiletest.cc
	testmain.cc
)
include_directories(${CPPUNIT_INCLUDE_DIR})
target_link_libraries(ut.json json ${CPPUNIT_LIBRARY})

set(ut_json_path ${CMAKE_SOURCE_DIR}/ut/testdata/)
add_definitions(-DUT_JSON_PATH=\"${ut_json_path}\")
