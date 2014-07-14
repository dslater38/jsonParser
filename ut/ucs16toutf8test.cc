#include <codecvt>
#include <locale>
#include <string>

#include <cppunit/extensions/HelperMacros.h>

#include "ucs16toutf8.hh"

using JSON::helper::ucs16toutf8;

class Ucs16ToUtf8Test : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(Ucs16ToUtf8Test);

    CPPUNIT_TEST(testConversion);

	CPPUNIT_TEST_SUITE_END();
    
    void testConversion()
    {
        std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> stdMultiByteConverter;

        for (char16_t codePoint { 0x0000 }; codePoint <= 0xD7FF; ++codePoint) {
            CPPUNIT_ASSERT_EQUAL(
                    stdMultiByteConverter.to_bytes(codePoint), ucs16toutf8(codePoint));
        }

        // skipping surrogates

        for (char16_t codePoint { 0xE000 }; codePoint <= 0xFFFFu; ++codePoint) {
            CPPUNIT_ASSERT_EQUAL(
                    stdMultiByteConverter.to_bytes(codePoint), ucs16toutf8(codePoint));
            if (codePoint == 0xFFFF) break;
        }
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION(Ucs16ToUtf8Test);

