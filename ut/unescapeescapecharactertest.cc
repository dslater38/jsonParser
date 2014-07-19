#include <cppunit/extensions/HelperMacros.h>

#include "unescape.hh"

using JSON::helper::unescape;

class UnescapeEscapeCharacterTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UnescapeEscapeCharacterTest);

    CPPUNIT_TEST(testEmptyInput);
    CPPUNIT_TEST(testInputWithNoOccurrances);
    CPPUNIT_TEST(testOccurranceAtBegin);
    CPPUNIT_TEST(testOccurranceMiddle);
    CPPUNIT_TEST(testOccurranceAtEnd);
    CPPUNIT_TEST(testMultipleOccurrancesContiguous);
    CPPUNIT_TEST(testMultipleOccurrancesSpaced);
    CPPUNIT_TEST(testWithPartialMatch);

	CPPUNIT_TEST_SUITE_END();
    
    void testEmptyInput();
    void testInputWithNoOccurrances();
    void testOccurranceAtBegin();
    void testOccurranceMiddle();
    void testOccurranceAtEnd();
    void testMultipleOccurrancesContiguous();
    void testMultipleOccurrancesSpaced();
    void testWithPartialMatch();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnescapeEscapeCharacterTest);

void UnescapeEscapeCharacterTest::testEmptyInput()
{
    std::string s { R"()" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{""}, s);
}

void UnescapeEscapeCharacterTest::testInputWithNoOccurrances()
{
    std::string s { R"(nothing to replace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"nothing to replace"}, s);
}

void UnescapeEscapeCharacterTest::testOccurranceAtBegin()
{
    std::string s { R"(\tto replace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"\tto replace"}, s);
}

void UnescapeEscapeCharacterTest::testOccurranceMiddle()
{
    std::string s { R"(to \treplace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to \treplace"}, s);
}

void UnescapeEscapeCharacterTest::testOccurranceAtEnd()
{
    std::string s { R"(to replace\t)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to replace\t"}, s);
}

void UnescapeEscapeCharacterTest::testMultipleOccurrancesContiguous()
{
    std::string s { R"(to \t\treplace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to \t\treplace"}, s);
}

void UnescapeEscapeCharacterTest::testMultipleOccurrancesSpaced()
{
    std::string s { R"(to \tre\tplace)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"to \tre\tplace"}, s);
}

void UnescapeEscapeCharacterTest::testWithPartialMatch()
{
    std::string s { R"(to \eplace)" };
    CPPUNIT_ASSERT_THROW(unescape(s), std::runtime_error);
}

