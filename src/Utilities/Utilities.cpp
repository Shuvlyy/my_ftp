#include "Utilities/Utilities.hpp"

#include <algorithm>
#include <sstream>

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
