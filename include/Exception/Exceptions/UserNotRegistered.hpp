#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class UserNotRegistered final
        : public AException
    {
    public:
        explicit UserNotRegistered(const std::string &username)
            : AException(username + ": Unknown user ; not registered.")
        {}
    };

}
