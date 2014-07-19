#include <cppunit/extensions/HelperMacros.h>

#include "unescape.hh"

using JSON::helper::unescape;

class UnescapeJsonEscapeCharacterTest : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(UnescapeJsonEscapeCharacterTest);

    CPPUNIT_TEST(testQuotationMark);
    CPPUNIT_TEST(testReverseSolidus);
    CPPUNIT_TEST(testSolidus);
    CPPUNIT_TEST(testBackspace);
    CPPUNIT_TEST(testFormfeed);
    CPPUNIT_TEST(testNewline);
    CPPUNIT_TEST(testCarriageReturn);
    CPPUNIT_TEST(testHorizontalTab);

    CPPUNIT_TEST(testReplacementIsPartOfAnotherEscape);
    CPPUNIT_TEST(testReplacementIsPartOfAnotherEscape2);

	CPPUNIT_TEST_SUITE_END();
    
    void testQuotationMark();
    void testReverseSolidus();
    void testSolidus();
    void testBackspace();
    void testFormfeed();
    void testNewline();
    void testCarriageReturn();
    void testHorizontalTab();

    void testReplacementIsPartOfAnotherEscape();
    void testReplacementIsPartOfAnotherEscape2();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnescapeJsonEscapeCharacterTest);

// cf. http://www.ecma-international.org/publications/files/ecma-st/ECMA-262.pdf, 15.12.1.1

void UnescapeJsonEscapeCharacterTest::testQuotationMark()
{
    std::string s { R"(\")" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\"'}, s);
}

void UnescapeJsonEscapeCharacterTest::testReverseSolidus()
{
    std::string s { R"(\\)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\\'}, s);
}

void UnescapeJsonEscapeCharacterTest::testSolidus()
{
    std::string s { R"(\/)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'/'}, s);
}

void UnescapeJsonEscapeCharacterTest::testBackspace()
{
    std::string s { R"(\b)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\b'}, s);
}

void UnescapeJsonEscapeCharacterTest::testFormfeed()
{
    std::string s { R"(\f)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\f'}, s);
}

void UnescapeJsonEscapeCharacterTest::testNewline()
{
    std::string s { R"(\n)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\n'}, s);
}

void UnescapeJsonEscapeCharacterTest::testCarriageReturn()
{
    std::string s { R"(\r)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\r'}, s);
}

void UnescapeJsonEscapeCharacterTest::testHorizontalTab()
{
    std::string s { R"(\t)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{'\t'}, s);
}

void UnescapeJsonEscapeCharacterTest::testReplacementIsPartOfAnotherEscape()
{
    std::string s { R"(\\\/)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"\\/"}, s);
}

void UnescapeJsonEscapeCharacterTest::testReplacementIsPartOfAnotherEscape2()
{
    std::string s { R"(\\\\t)" };
    unescape(s);
    CPPUNIT_ASSERT_EQUAL(std::string{"\\\\t"}, s);
}

