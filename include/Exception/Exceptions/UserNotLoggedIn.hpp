#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class UserNotLoggedIn final
        : public AException
    {
    public:
        explicit UserNotLoggedIn(const int fd)
            : AException(fd + ": User not logged in.")
        {}
    };

}
