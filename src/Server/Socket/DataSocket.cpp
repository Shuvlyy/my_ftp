#include "Server/Socket/DataSocket.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <arpa/inet.h>

ftp::server::DataSocket::DataSocket
(
    const std::string &clientIp,
    const short clientPort
)
    : Socket(clientPort),
      _state(ACTIVE)
{
    if (inet_pton(
        AF_INET,
        clientIp.c_str(),
        &this->_address.sin_addr
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("inet_pton");
    }

    if (connect(
        this->_fd,
        reinterpret_cast<sockaddr *>(&this->_address),
        sizeof(this->_address)
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("connect");
    }
}

ftp::server::DataSocket::DataSocket
()
    : Socket(static_cast<short>(0)),
      _state(PASSIVE)
{
    socklen_t addressLen = sizeof(this->_address);

    if (getsockname(
        this->_fd,
        reinterpret_cast<sockaddr *>(&this->_address),
        &addressLen
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("getsockname");
    }

    this->startListening();
}

void
ftp::server::DataSocket::acceptConnection
()
{
    const int newFd = accept(this->getFd(), nullptr, nullptr);

    if (newFd < 0) {
        throw exception::StandardFunctionFail("accept");
    }

    this->closeSocket();
    this->_fd = newFd;
}
