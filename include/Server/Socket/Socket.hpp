#pragma once

#define PROTOCOL_ANY        0
#define BUFFER_SIZE         1024
#define DEFAULT_MAX_CLIENTS 192
#define CRLF                "\r\n"

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
         * @param   data        Data to write
         * @param   withCrlf    If set to true, will append a CRLF at the end of the sent packet.
         */
        void send(const std::string &data, bool withCrlf = true) const;

        /**
         * Reads from the file descriptor and returns its content.
         */
        [[nodiscard]] std::string receive();

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

        void startListening(int maxClients);

    protected:
        int _fd;
        sockaddr_in _address;
        std::string _bufferCache;
    };

}
