#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class WdOutOfScope final
        : public AException
    {
    public:
        explicit WdOutOfScope(const std::string &wd)
            : AException("Directory out of scope: \"" + wd + "\"")
        {}
    };

}
