#include "Logger/Log.hpp"

#include <ctime>
#include <sstream>

ftp::logger::Log::Log
(
    const Level level,
    std::string authorIp,
    std::string authorUser,
    std::string body,
    std::string response
)
    : _level(level),
      _creationTime(time(nullptr)),
      _authorIp(std::move(authorIp)),
      _authorUser(std::move(authorUser)),
      _body(std::move(body)),
      _response(std::move(response))
{}

std::string
ftp::logger::Log::compute
()
    const
{
    std::stringstream ss;

    /*  Format:                                                                                */
    /* "[2025-11-03 13:53:19] <INFO>    192.168.1.40    admin   CWD include/    200 CWD okay." */
    ss  << "[" << this->formatCreationTime() << "] <" << this->_level << "> "
        << this->_authorIp << "\t"
        << this->_authorUser << "\t"
        << this->_body << "\t"
        << this->_response
        << std::endl;

    return ss.str();
}

std::string
ftp::logger::Log::formatCreationTime
()
    const
{
    const tm time = *localtime(&this->_creationTime);
    char buf[20];

    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &time);
    return buf;
}
