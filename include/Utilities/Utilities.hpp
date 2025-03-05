#pragma once

#include <string>

namespace ftp
{

    class Utilities
    {
    public:
        static int stringToInt(const std::string& str);
        static std::string stringToUpper(const std::string &str);
        static std::string cleanString(const std::string &str);
    };

}
