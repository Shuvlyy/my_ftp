#pragma once

#include "Exception/AException.hpp"

#include <string>

namespace ftp::exception
{

    class UnknownFlag final
        : public AException
    {
    public:
        explicit UnknownFlag(const std::string &flag)
            : AException("Unknown flag: " + flag + ".\nUse -help flag for help.")
        {}
    };

}
