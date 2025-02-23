#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class Impossible final
        : public AException
    {
    public:
        explicit Impossible()
            : AException("erm what the sigma")
        {}
    };

}
