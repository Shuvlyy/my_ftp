#pragma once

#define PROTOCOL_ANY    0
#define BUFFER_SIZE     1024
#define MAX_CLIENTS     16

#include <string>

namespace ftp::server
{

    class Socket final
    {
    public:
        /**
         * Creates a server socket.
         *
         * @param   port   Port to listen to
         */
        explicit Socket(short port);

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
         * Closes the socket: its file descriptor.
         */
        void closeSocket();

        /**
         * @return Socket's file descriptor
         */
        [[nodiscard]] int getFd() const;

        void startListening() const;

    private:
        int _fd;
    };

}
