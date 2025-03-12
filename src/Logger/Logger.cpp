#include "Logger/Logger.hpp"

void
ftp::Logger::log
(
    const logger::Log &log
)
{
    this->_logs.push_back(log);
}
