#include "Server/Socket/Socket.hpp"

#include "Exception/Exceptions/ClientDisconnected.hpp"
#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

ftp::server::Socket::Socket
(
    const short port
)
{
    this->_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL_ANY);

    if (this->_fd < 0) {
        throw exception::StandardFunctionFail("socket");
    }

    sockaddr_in serverAddress {};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(
        this->_fd,
        reinterpret_cast<sockaddr *>(&serverAddress),
        sizeof(serverAddress)
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("bind");
    }
}

ftp::server::Socket::Socket
(
    const int fd
)
    : _fd(fd)
{}

void
ftp::server::Socket::send
(
    const std::string &data
)
    const
{
    if (this->_fd == -1) {
        return;
    }

    const std::string dataToSend(data + "\r\n");

    const ssize_t bytesWritten = write(
        this->_fd,
        dataToSend.c_str(),
        dataToSend.length()
    );

    if (bytesWritten == -1) {
        throw exception::StandardFunctionFail("write");
    }
}

std::string
ftp::server::Socket::receive
()
    const
{
    std::string result;
    ssize_t bytesRead;

    while (true) {
        if (this->_fd == -1) {
            return "";
        }

        char buffer[BUFFER_SIZE];

        bytesRead = read(this->_fd, buffer, BUFFER_SIZE);

        if (bytesRead < 0) {
            throw exception::StandardFunctionFail("read");
        }

        if (bytesRead == 0) {
            throw exception::ClientDisconnected(this->getFd());
        }

        buffer[bytesRead] = '\0';
        result.append(buffer, bytesRead);

        if (result.size() >= 2 && result.ends_with("\r\n")) {
            break;
        }
    }

    /* Removing <CRLF> (\r\n, last two characters) */
    result.pop_back();
    result.pop_back();

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
    if (listen(this->_fd, MAX_CLIENTS) < 0) {
        close(this->_fd);
        throw exception::StandardFunctionFail("listen");
    }
}
