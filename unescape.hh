#include <codecvt>
#include <locale>
#include <string>

namespace JSON {

    namespace helper {

        /**
         * @brief Replace all occurrences of an escaped character by its unescaped version.
         *
         * @param s String containing zero or more occurrences of the character to replace
         * @param toReplace C-style string to replace
         * @param ch C-style string to replace with
         *
         * @pre toReplace must not be null
         */
        inline void unescapeEscapeCharacter(
                std::string& s, const char* const toReplace, const char* const ch)
        {
            std::string::size_type n { };

            while (true) {
                n = s.find(toReplace, n);
                if (n == std::string::npos) break;
                s.replace(n, 2, ch);
            }
        }

        //   \uFFFF -> unicode character UTF-8
        inline void unescapeUnicodeEspaceSequence(std::string& s)
        {
            std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> multiByteConverter;

            std::size_t n { };

            while (true) {
                n = s.find("\\u", n);
                if (n == std::string::npos) break;
                const std::string codePointStr { s.substr(n + 2, 4) };
                const char16_t codePoint { static_cast<char16_t>(std::stoul(codePointStr, 0, 16)) };
                s.replace(n, 6, multiByteConverter.to_bytes(codePoint));
            }
        }

        inline void unescape(std::string& s)
        {
            unescapeEscapeCharacter(s, "\\\"", "\"");
            unescapeEscapeCharacter(s, "\\\\", "\\");
            unescapeEscapeCharacter(s, "\\/", "/");
            unescapeEscapeCharacter(s, "\\b", "\b");
            unescapeEscapeCharacter(s, "\\f", "\f");
            unescapeEscapeCharacter(s, "\\n", "\n");
            unescapeEscapeCharacter(s, "\\r", "\r");
            unescapeEscapeCharacter(s, "\\t", "\t");
        }

    }

}

