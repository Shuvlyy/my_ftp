#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class FileNotFound final
        : public AException
    {
    public:
        explicit FileNotFound(const std::string &filepath)
            : AException(filepath + ": File not found")
        {}
    };

}
