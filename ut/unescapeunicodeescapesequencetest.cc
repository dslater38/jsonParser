#include <cppunit/extensions/HelperMacros.h>

#include "unescape.hh"

using JSON::helper::unescapeUnicodeEscapeSequence;

class UnescapeUnicodeEscapeSequenceTest : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(UnescapeUnicodeEscapeSequenceTest);

    CPPUNIT_TEST(testBasicLatin);
    CPPUNIT_TEST(testLatin1Supplement);
    CPPUNIT_TEST(testLatinExtendedA);
    CPPUNIT_TEST(testMyanmar);
    CPPUNIT_TEST(testPhoneticExtensions);
    CPPUNIT_TEST(testGreekExtended);
    CPPUNIT_TEST(testHiragana);
    CPPUNIT_TEST(testCJK);

    CPPUNIT_TEST_SUITE_END();

    void testBasicLatin();
    void testLatin1Supplement();
    void testLatinExtendedA();
    void testMyanmar();
    void testPhoneticExtensions();
    void testGreekExtended();
    void testHiragana();
    void testCJK();

};

CPPUNIT_TEST_SUITE_REGISTRATION(UnescapeUnicodeEscapeSequenceTest);

// cf. http://www.ecma-international.org/publications/files/ecma-st/ECMA-262.pdf, 15.12.1.1

void UnescapeUnicodeEscapeSequenceTest::testBasicLatin()
{
    std::string s { u8R"(\u0041\u0042\u0043)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"ABC"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testLatin1Supplement()
{
    std::string s { u8R"(\u00A5\u00A3)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u00A5\u00A3"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testLatinExtendedA()
{
    std::string s { u8R"(\u0160\u0161)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u0160\u0161"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testMyanmar()
{
    std::string s { u8R"(\u1042\u1043)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u1042\u1043"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testPhoneticExtensions()
{
    std::string s { u8R"(\u1D19\u1D1A)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u1D19\u1D1A"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testGreekExtended()
{
    std::string s { u8R"(\u1f63\u1f64)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u1f63\u1f64"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testHiragana()
{
    std::string s { u8R"(\u3042\u3044\u3046\u3048\u304A)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u3042\u3044\u3046\u3048\u304A"}, s);
}

void UnescapeUnicodeEscapeSequenceTest::testCJK()
{
    std::string s { u8R"(\u4E0A\u4E0B)" };
    unescapeUnicodeEscapeSequence(s);
    CPPUNIT_ASSERT_EQUAL(std::string{u8"\u4E0A\u4E0B"}, s);
}

