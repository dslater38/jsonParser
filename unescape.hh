#include <string>

namespace JSON {

    namespace helper {

        inline void unescape(std::string& s)
        {
            while(true) {
                auto n = s.find("\\\""); // searches \"
                if (n == std::string::npos) break;
                s.replace(n, 2, "\""); // replaces with "
            }
        }

    }

}

