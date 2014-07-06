#include <limits>

#include <cppunit/extensions/HelperMacros.h>

#include "json_st.hh"

class ValueTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(ValueTest);

	CPPUNIT_TEST(testLongLongInt);
    CPPUNIT_TEST(testLongInt);
    CPPUNIT_TEST(testInt);

    CPPUNIT_TEST(testIntegerRangeMin);
    CPPUNIT_TEST(testIntegerRangeMax);

    CPPUNIT_TEST(testLongDouble);
    CPPUNIT_TEST(testDouble);

    CPPUNIT_TEST(testFloatingRangeMin);
    CPPUNIT_TEST(testFloatingRangeMax);

    CPPUNIT_TEST(testBoolTrue);
    CPPUNIT_TEST(testBoolFalse);

    CPPUNIT_TEST(testStringFromCharacterArray);
    CPPUNIT_TEST(testStringFromStl);

	CPPUNIT_TEST_SUITE_END();
    
    void testLongLongInt();
    void testLongInt();
    void testInt();

    void testIntegerRangeMin();
    void testIntegerRangeMax();

    void testLongDouble();
    void testDouble();

    void testFloatingRangeMin();
    void testFloatingRangeMax();

    void testBoolTrue();
    void testBoolFalse();

    void testStringFromCharacterArray();
    void testStringFromStl();
    
};

CPPUNIT_TEST_SUITE_REGISTRATION(ValueTest);

void ValueTest::testLongLongInt()
{
    constexpr long long content { 1ll };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_int());
    CPPUNIT_ASSERT_EQUAL(content, static_cast<long long>(v));
}

void ValueTest::testLongInt()
{
    constexpr long content { 1l };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), v.as_int());
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), static_cast<long long>(v));
}

void ValueTest::testInt()
{
    constexpr int content { 1 };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), v.as_int());
    CPPUNIT_ASSERT_EQUAL(static_cast<long long>(content), static_cast<long long>(v));
}

void ValueTest::testIntegerRangeMin()
{
    constexpr long long content { std::numeric_limits<long long>::min() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_int());
}

void ValueTest::testIntegerRangeMax()
{
    constexpr long long content { std::numeric_limits<long long>::max() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_int());
}

void ValueTest::testLongDouble()
{
    constexpr long double content { 0.333333333333333333l };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_float());
    CPPUNIT_ASSERT_EQUAL(content, static_cast<long double>(v));
}

void ValueTest::testDouble()
{
    constexpr double content { -0.3 };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(static_cast<long double>(content), v.as_float());
    CPPUNIT_ASSERT_EQUAL(static_cast<long double>(content), static_cast<long double>(v));
}

void ValueTest::testFloatingRangeMin()
{
    constexpr long double content { std::numeric_limits<long double>::min() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_float());
}

void ValueTest::testFloatingRangeMax()
{
    constexpr long double content { std::numeric_limits<long double>::max() };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_float());
}

void ValueTest::testBoolTrue()
{
    const JSON::Value v { true };
    CPPUNIT_ASSERT(v);
    CPPUNIT_ASSERT(v.as_bool());
}

void ValueTest::testBoolFalse()
{
    const JSON::Value v { false };
    CPPUNIT_ASSERT(not v);
    CPPUNIT_ASSERT(not v.as_bool());
}

void ValueTest::testStringFromCharacterArray()
{
    const char* content { "json++" };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(std::string{content}, v.as_string());
}

void ValueTest::testStringFromStl()
{
    const std::string content { "json++" };
    const JSON::Value v { content };
    CPPUNIT_ASSERT_EQUAL(content, v.as_string());
}

