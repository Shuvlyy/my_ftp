#include "Utilities/Utilities.hpp"

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
