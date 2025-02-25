#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class UnknownCommand final
        : public AException
    {
    public:
        explicit UnknownCommand(const std::string &command)
            : AException(command + ": Unknown command.")
        {}
    };

}
