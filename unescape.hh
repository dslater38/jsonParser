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

