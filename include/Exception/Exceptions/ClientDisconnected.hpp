#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class ClientDisconnected final
        : public AException
    {
    public:
        explicit ClientDisconnected(const int fd)
            : AException(fd + ": Client disconnected.")
        {}
    };

}
