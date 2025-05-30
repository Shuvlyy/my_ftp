#include "Server/Socket/Socket.hpp"

#include "Exception/Exceptions/ClientDisconnected.hpp"
#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

ftp::server::Socket::Socket
(
    const unsigned short port
)
    : _address{}
{
    this->_fd = socket(AF_INET, SOCK_STREAM, PROTOCOL_ANY);
    int opt = 0;

    if (this->_fd < 0) {
        throw exception::StandardFunctionFail("socket");
    }

    this->_address.sin_family = AF_INET;
    this->_address.sin_addr.s_addr = INADDR_ANY;
    this->_address.sin_port = htons(port);

    if (setsockopt(
        this->_fd,
        SOL_SOCKET,
        SO_REUSEADDR,
        &opt,
        sizeof(opt)
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("setsockopt");
    }
}

ftp::server::Socket::Socket
(
    const int fd
)
    : _fd(fd), _address{}
{}

void
ftp::server::Socket::send
(
    const std::string &data,
    const bool withCrlf
)
    const
{
    if (this->_fd == -1) {
        return;
    }

    std::string dataToSend(data);

    if (withCrlf) {
        dataToSend += CRLF;
    }

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
{
    while (true) {
        if (this->_fd == -1) {
            return "";
        }

        char buffer[BUFFER_SIZE];
        const ssize_t bytesRead = read(this->_fd, buffer, BUFFER_SIZE);

        if (bytesRead < 0) {
            throw exception::StandardFunctionFail("read");
        }

        if (bytesRead == 0) {
            throw exception::ClientDisconnected(this->_fd);
        }

        buffer[bytesRead] = '\0';

        this->_bufferCache.append(buffer, bytesRead);

        const size_t crlfPos = this->_bufferCache.find(CRLF);

        if (crlfPos != std::string::npos) {
            std::string result = this->_bufferCache.substr(0, crlfPos);
            this->_bufferCache = this->_bufferCache.substr(crlfPos + 2); // Keeping in cache what's after CRLF.
            return result;
        }
    }
}

std::string
ftp::server::Socket::receiveBinary
()
    const
{
    if (this->_fd == -1) {
        return "";
    }

    char buffer[BUFFER_SIZE];
    const ssize_t bytesRead = read(this->_fd, buffer, BUFFER_SIZE);

    if (bytesRead < 0) {
        throw exception::StandardFunctionFail("read");
    }

    if (bytesRead == 0) {
        return ""; // EOF, ignored for file transfers
    }

    return {
        buffer,
        static_cast<std::string::size_type>(bytesRead)
    }; // Different way to initialize a string
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
(
    const int maxClients
)
{
    if (bind(
        this->_fd,
        reinterpret_cast<sockaddr *>(&this->_address),
        sizeof(this->_address)
    ) < 0) {
        this->closeSocket();
        throw exception::StandardFunctionFail("bind");
    }

    if (listen(this->_fd, maxClients) < 0) {
        close(this->_fd);
        throw exception::StandardFunctionFail("listen");
    }
}

sockaddr_in &
ftp::server::Socket::getAddress
()
{
    return this->_address;
}
