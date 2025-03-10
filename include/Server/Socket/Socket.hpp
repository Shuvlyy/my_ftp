#pragma once

#define PROTOCOL_ANY    0
#define BUFFER_SIZE     1024
#define MAX_CLIENTS     64

#include <string>
#include <netinet/in.h>

namespace ftp::server
{

    class Socket
    {
    public:
        /**
         * Creates a server socket.
         *
         * @param   port   Port to listen to
         */
        explicit Socket(unsigned short port);

        /**
         * Creates a client socket, from an existing file descriptor.
         *
         * @param   fd     File descriptor
         */
        explicit Socket(int fd);

        ~Socket() = default;

        /**
         * Writes the given string into the file descriptor.
         *
         * @param   data    Data to write
         */
        void send(const std::string &data) const;

        /**
         * Reads from the file descriptor and returns its content.
         */
        [[nodiscard]] std::string receive() const;

        /**
         * Reads from the file descriptor and returns its content.
         * Only reads with a size of BUFFER_SIZE.
         * Specially made for data transfer (c.f. command::Stor::startDownload).
         */
        [[nodiscard]] std::string receiveBinary() const;

        /**
         * Closes the socket: its file descriptor.
         */
        void closeSocket();

        /**
         * @return Socket's file descriptor
         */
        [[nodiscard]] int getFd() const;

        [[nodiscard]] sockaddr_in &getAddress();

        void startListening();

    protected:
        int _fd;
        sockaddr_in _address;
    };

}
