#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class PathIsNotDir final
        : public AException
    {
    public:
        explicit PathIsNotDir(const std::string &wd)
            : AException("Path is not directory: \"" + wd + "\"")
        {}
    };

}
