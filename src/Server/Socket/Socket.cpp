#include "Server/Socket/Socket.hpp"

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fcntl.h>

ftp::server::Socket::Socket
(
    short port
)
{
    this->_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL_ANY);

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

    /* Make socket non-blocking. */
    fcntl(this->_fd, F_SETFL, O_NONBLOCK);
}

ftp::server::Socket::Socket
(
    int fd
)
    : _fd(fd)
{
    /* Make socket non-blocking. */
    fcntl(_fd, F_SETFL, O_NONBLOCK);
}

ftp::server::Socket::~Socket
()
{
    this->closeSocket();
}

void
ftp::server::Socket::send
(
    const std::string &data
)
    const
{
    const ssize_t bytesWritten =
        write(this->_fd, data.c_str(), data.length());

    if (bytesWritten == -1) {
        // TODO: Throw exception
    }
}

std::string
ftp::server::Socket::receive
()
    const
{
    std::string result;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = 1;

    while (bytesRead > 0) {
        bytesRead = read(this->_fd, buffer, BUFFER_SIZE);
        result.append(buffer, bytesRead);
    }

    if (bytesRead == -1) {
        // TODO: Throw exception
    }

    return result;
}

void
ftp::server::Socket::closeSocket
()
{
    /* If socket has already been closed, don't continue */
    if (this->_fd == -1) {
        return;
    }

    close(this->_fd);
    this->_fd = -1;
}

int
ftp::server::Socket::getFd
()
    const
{
    return this->_fd;
}

void
ftp::server::Socket::startListening
()
    const
{
    if (listen(this->_fd, 5) < 0) { // FIXME: 5 is magic number (represents the max amount of simultaneous connections)
        close(this->_fd);
        // TODO: Throw exception
    }
}
