#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class InvalidUsage final
        : public AException
    {
    public:
        explicit InvalidUsage()
            : AException("Invalid usage. Use -help flag for help.")
        {}
    };

}
