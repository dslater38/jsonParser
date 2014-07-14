#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "json.hh"
#include "json_st.hh"

class ParseFileTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(ParseFileTest);

    CPPUNIT_TEST(testString);
	CPPUNIT_TEST(testNumber);
    CPPUNIT_TEST(testBool);
    CPPUNIT_TEST(testNull);

	CPPUNIT_TEST_SUITE_END();
    
    void testString();
    void testNumber();
    void testBool();
    void testNull();

};

CPPUNIT_TEST_SUITE_REGISTRATION(ParseFileTest);

void ParseFileTest::testString()
{
    const std::string fileName { std::string{UT_JSON_PATH} + "string.json" };

    const JSON::Value v { parse_file(fileName.c_str()) };

    CPPUNIT_ASSERT_EQUAL(std::string{}, v["empty"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{"c"}, v["one char"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{"a lot of characters"}, v["chars"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{"\u00D6\u00F6"}, v["unicode"].as_string());
    CPPUNIT_ASSERT_EQUAL(std::string{"europa\"great"}, v["escaped quotation mark"].as_string());
}

void ParseFileTest::testNumber()
{
    const std::string fileName { std::string{UT_JSON_PATH} + "number.json" };

    const JSON::Value v { parse_file(fileName.c_str()) };

    // cf. grammar http://json.org

    CPPUNIT_ASSERT_EQUAL(3ll, v["int one digit"].as_int());
    CPPUNIT_ASSERT_EQUAL(123ll, v["int digits"].as_int());
    CPPUNIT_ASSERT_EQUAL(-9ll, v["int one digit negative"].as_int());
    CPPUNIT_ASSERT_EQUAL(-421ll, v["int digits negative"].as_int());

    CPPUNIT_ASSERT_DOUBLES_EQUAL(123.4l, v["int frac positive"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(-456.789l, v["int frac negative"].as_float(), 1e-5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e0l, v["int exp e"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e6l, v["int exp e+"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e-7l, v["int exp e-"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e8l, v["int exp E"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e9l, v["int exp E+"].as_float(), 1e-5);
    CPPUNIT_ASSERT_DOUBLES_EQUAL(123e-1l, v["int exp E-"].as_float(), 1e-5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(-123.4e-4l, v["int frac exp"].as_float(), 1e-5);

    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0l, v["number zero float"].as_float(), 1e-5);
    CPPUNIT_ASSERT_EQUAL(0ll, v["number zero integer"].as_int());

    CPPUNIT_ASSERT_EQUAL(9223372036854775807ll, v["long long max"].as_int());
    CPPUNIT_ASSERT_EQUAL(-9223372036854775807ll, v["long long min"].as_int());
}

void ParseFileTest::testBool()
{
    const std::string fileName { std::string{UT_JSON_PATH} + "bool.json" };

    const JSON::Value v { parse_file(fileName.c_str()) };

    CPPUNIT_ASSERT(v["true"]);
    CPPUNIT_ASSERT(not v["false"]);
}

void ParseFileTest::testNull()
{
    const std::string fileName { std::string{UT_JSON_PATH} + "null.json" };

    const JSON::Value v { parse_file(fileName.c_str()) };

    CPPUNIT_ASSERT_EQUAL(JSON::NIL, v["null"].type());
}

