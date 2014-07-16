#include <stdexcept>
#include <string>

namespace JSON {

    namespace helper {

        /**
         * @brief Convert 16 bit code point to UTF-8 string.
         *
         * Conversion implemented according to:
         *
         * http://www.unicode.org/versions/Unicode6.2.0/ch03.pdf#G7404
         * Table 3-6. UTF-8 Bit Distribution
         * -------------------|------------|------------|------------|
         * Scalar Value       |  1st Byte  |  2nd Byte  |  3rd Byte  |
         * -------------------|------------|------------|------------|
         * 00000000 0xxxxxxx  |  0xxxxxxx  |            |            |  (1)
         * 00000yyy yyxxxxxx  |  110yyyyy  |  10xxxxxx  |            |  (2)
         * zzzzyyyy yyxxxxxx  |  1110zzzz  |  10yyyyyy  |  10xxxxxx  |  (3)
         * -------------------|------------|------------|------------|
         * 87654321 87654321  |  87654321  |  87654321  |  87654321  |
         * -------------------|------------|------------|------------|
         *
         * @param codepoint
         *
         * @return string containing at most 3 bytes representing the code point
         */
        inline std::string codePoint2utf8(const char16_t codepoint)
        {
            /*  (1)  */
            if (codepoint <= 0x007F) return { static_cast<char>(codepoint) };

            /*  (2)  */
            if (codepoint <= 0x07FF) {
                const unsigned char firstByte = 0xC0 + ((codepoint & 0x07C0 ) >> 6);
                const unsigned char secondByte = 0x80 + (codepoint & 0x003F);
                return { static_cast<char>(firstByte), static_cast<char>(secondByte) };
            }

            /*  (3)  */
            if (codepoint <= 0xFFFF) {
                const unsigned char firstByte = 0xE0 + ((codepoint & 0xF000 ) >> 12);
                const unsigned char secondByte = 0x80 + ((codepoint & 0x0FC0 ) >> 6);
                const unsigned char thirdByte = 0x80 + (codepoint & 0x003F);
                return { static_cast<char>(firstByte), static_cast<char>(secondByte), static_cast<char>(thirdByte) };
            }

            return { };  // can never happen
        }

    }

}
