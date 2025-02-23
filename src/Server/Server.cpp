#include "Server/Server.hpp"

#include <iostream>
#include <utility>
#include <unistd.h>

ftp::Server::Server
(
    short port,
    std::string path
)
    : _serverFd(0),
      _address{},
      _addressLen{},
      _port(port),
      _isRunning(false),
      anonymousUserHomePath(std::move(path))
{
    this->initialize();
}

ftp::Server::~Server
()
{
    this->terminate();
}

void
ftp::Server::start
()
{
    this->_isRunning = true;

    while (this->_isRunning) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientFd = accept(
            this->_serverFd,
            reinterpret_cast<sockaddr *>(&clientAddr),
            &clientAddrLen
        );

        if (clientFd < 0) {
            std::cout << "accept fail" << std::endl;
            throw std::exception(); // TODO: Throw proper exception.
        }

        write(clientFd, "I lost the game :3\n", 19);
        close(clientFd);
    }
}

void
ftp::Server::stop
()
{
    this->_isRunning = false;
    close(this->_serverFd);
}

void
ftp::Server::initialize
()
{
    int ret;
    int opt = 1;

    this->_address.sin_family = AF_INET;           // Uses IPV4
    this->_address.sin_addr.s_addr = INADDR_ANY;   // Accepts incoming connections from every IP
    this->_address.sin_port = htons(this->_port);  // Sets the port

    this->_serverFd = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    if (this->_serverFd < 0) {
        throw std::exception(); // TODO: Throw proper exception.
    }

    ret = setsockopt(
        this->_serverFd,
        SOL_SOCKET,
        SO_REUSEADDR | SO_REUSEPORT,
        &opt,
        sizeof(opt)
    );

    if (ret < 0) {
        throw std::exception(); // TODO: Throw proper exception.
    }

    ret = bind(
        this->_serverFd,
        reinterpret_cast<sockaddr *>(&this->_address),
        sizeof(this->_address)
    );

    if (ret < 0) {
        throw std::exception(); // TODO: Throw proper exception.
    }

    ret = listen(this->_serverFd, 1);

    if (ret != 0) {
        throw std::exception();
    }
}

void
ftp::Server::terminate
()
{
    this->stop();
}
