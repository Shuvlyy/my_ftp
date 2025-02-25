#include "Server/Socket/Socket.hpp"

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

ftp::server::Socket::Socket
(
    short port
)
    : _fd()
{
    this->initialize(port);
}

int
ftp::server::Socket::getFd
()
    const
{
    return this->_fd;
}

void
ftp::server::Socket::initialize
(
    short port
)
{
    this->_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_fd < 0) {
        // TODO: Throw exception
    }

    sockaddr_in serverAddr {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(this->_fd, (sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
        close(this->_fd);
        // TODO: Throw exception
    }

    if (listen(this->_fd, 5) < 0) { // FIXME: 5 is magic number (represents the max amount of simultaneous connections)
        close(this->_fd);
        // TODO: Throw exception
    }

    /* Make socket non-blocking. */
    fcntl(this->_fd, F_SETFL, O_NONBLOCK);
}
