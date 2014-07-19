#ifndef JSON_HELPER_UNESCAPE_HH
#define JSON_HELPER_UNESCAPE_HH

#include <stdexcept>
#include <string>

#include "codepoint2utf8.hh"

namespace JSON {

    namespace helper {

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
                            break;
                        }
                    default:
                        throw std::runtime_error("Unexpected escape character in " + s);
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
