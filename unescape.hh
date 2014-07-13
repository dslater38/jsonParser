#include <string>

namespace JSON {

    namespace helper {

        inline void unescapeEscapeCharacter(
                std::string& s, const char* const toReplace, const char* const ch)
        {
            while(true) {
                auto n = s.find(toReplace);
                if (n == std::string::npos) break;
                s.replace(n, 2, ch);
            }
        }

        inline void unescape(std::string& s)
        {
            unescapeEscapeCharacter(s, "\\\"", "\"");
        }

    }

}

