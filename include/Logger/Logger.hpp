#pragma once

#include "Logger/Log.hpp"

#include <vector>

namespace ftp
{

    class Logger final
    {
    public:
        void log(const logger::Log &log);

    private:
        std::vector<logger::Log> _logs;
    };

}
