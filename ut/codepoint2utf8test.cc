#include <codecvt>
#include <locale>
#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "codepoint2utf8.hh"

using JSON::helper::codePoint2utf8;

class CodePoint2Utf8Test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(CodePoint2Utf8Test);

    CPPUNIT_TEST(testConversion);

	CPPUNIT_TEST_SUITE_END();
    
    void testConversion()
    {
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> stdMultiByteConverter;

        for (char16_t codePoint { 0x0000 }; codePoint <= 0xD7FF; ++codePoint) {
            CPPUNIT_ASSERT_EQUAL(
                    stdMultiByteConverter.to_bytes(codePoint), codePoint2utf8(codePoint));
        }

        // skipping surrogates

        for (char16_t codePoint { 0xE000 }; codePoint <= 0xFFFFu; ++codePoint) {
            CPPUNIT_ASSERT_EQUAL(
                    stdMultiByteConverter.to_bytes(codePoint), codePoint2utf8(codePoint));
            if (codePoint == 0xFFFF) break;
        }
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION(CodePoint2Utf8Test);

