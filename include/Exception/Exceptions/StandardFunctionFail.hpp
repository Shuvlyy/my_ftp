#pragma once

#include <cstring>

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class StandardFunctionFail final
        : public AException
    {
    public:
        explicit StandardFunctionFail(const std::string &functionName)
            : AException(
                "Standard function fail: " + functionName + "\n" +
                "Error description: " + strerror(errno)
            )
        {}
    };

}
