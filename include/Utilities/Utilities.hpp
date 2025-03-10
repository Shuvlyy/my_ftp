#pragma once

#define SIX_MONTHS_SEC  15780000

#include <string>

namespace ftp
{

    class Utilities
    {
    public:
        static int stringToInt(const std::string& str);
        static std::string stringToUpper(const std::string &str);
        static std::string cleanString(const std::string &str);
        static std::string getDirContents(const std::string &filepath);
        static std::string getAbsolutePath(const std::string &root, const std::string &filepath);
    };

}
