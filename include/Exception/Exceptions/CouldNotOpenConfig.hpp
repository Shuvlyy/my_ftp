#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class CouldNotOpenConfig final
        : public AException
    {
    public:
        explicit CouldNotOpenConfig()
            : AException("Could not open config file")
        {}
    };

}
