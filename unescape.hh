#ifndef JSON_HELPER_UNESCAPE_HH
#define JSON_HELPER_UNESCAPE_HH

#include <string>

#include "codepoint2utf8.hh"

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
                ++n;
            }
        }

        inline void unescape(std::string& s)
        {
            std::string result;

            auto citer = s.cbegin();
            while (citer != s.cend()) {
                const auto c = *citer++;
                if (c == '\\') {
                    switch (*citer++) {
                    case '"': result += '\"'; break;
                    case '\\': result += '\\'; break;
                    case '/': result += '/'; break;
                    case 'b': result += '\b'; break;
                    case 'f': result += '\f'; break;
                    case 'n': result += '\n'; break;
                    case 't': result += '\t'; break;
                    case 'r': result += '\r'; break;
                    case 'u': {
                            const std::string codePointStr { citer, citer + 4 };
                            const char16_t codePoint {
                                static_cast<char16_t>(std::stoul(codePointStr, 0, 16)) };
                            result += codePoint2utf8(codePoint);
                            std::advance(citer, 4);
                        }
                    }
                }
                else {
                    result += c;
                }
            }

            s = std::move(result);
        }

    }

}

#endif
