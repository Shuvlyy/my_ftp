#include "Utilities/Utilities.hpp"

#include "Exception/Exceptions/FileNotFound.hpp"

#include <algorithm>
#include <sstream>
#include <filesystem>

int
ftp::Utilities::stringToInt
(
    const std::string &str
)
{
    std::istringstream iss(str);
    int res;

    iss >> res;
    return res;
}

std::string
ftp::Utilities::stringToUpper
(
    const std::string &str
)
{
    std::string s(str);

    std::transform(
        s.begin(),
        s.end(),
        s.begin(),
        [](const unsigned char c){
            return std::toupper(c);
        }
    );
    return s;
}

std::string
ftp::Utilities::cleanString
(
    const std::string &str
)
{
    const size_t first = str.find_first_not_of(" \t");
    if (first == std::string::npos) {
        return "";
    }

    const size_t last = str.find_last_not_of(" \t");
    return str.substr(first, last - first + 1);
}

std::string
ftp::Utilities::getAbsolutePath
(
    const std::string &root,
    const std::string &filepath
)
{
    namespace fs = std::filesystem;

    const fs::path path = fs::path(root) / fs::path(filepath);

    if (!exists(path)) {
        throw exception::FileNotFound(path);
    }
    return canonical(path).string();
}
