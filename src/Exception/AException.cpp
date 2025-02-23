#include "Exception/AException.hpp"

ftp::exception::AException::AException
(
    std::string message
)
    : _message(std::move(message))
{}

const char *
ftp::exception::AException::what
()
    const noexcept
{
    return this->_message.c_str();
}
