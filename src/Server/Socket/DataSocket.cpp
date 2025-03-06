#include "Server/Socket/DataSocket.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <arpa/inet.h>

ftp::server::DataSocket::DataSocket
(
    const std::string &clientIp,
    const unsigned short clientPort
)
    : Socket(clientPort),
      _state(ACTIVE)
{
    this->_address.sin_addr.s_addr = inet_addr(clientIp.c_str());

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
    : Socket(static_cast<unsigned short>(0)),
      _state(PASSIVE)
{
    socklen_t addressLen = sizeof(this->_address);

    this->startListening();

    if (getsockname(
        this->_fd,
        reinterpret_cast<sockaddr *>(&this->_address),
        &addressLen
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("getsockname");
    }
}

ftp::server::DataSocket::DataSocket(char)
    : Socket(-1),
      _state(DEADASS)
{}

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

void
ftp::server::DataSocket::closeSocket
()
{
    this->_state = DEADASS;
    this->Socket::closeSocket();
}
