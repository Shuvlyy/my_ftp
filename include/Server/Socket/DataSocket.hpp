#pragma once

#include "Server/Socket/Socket.hpp"

#include <netinet/in.h>

namespace ftp::server
{

    class DataSocket
        : public Socket
    {
    public:
        enum State
        {
            DEADASS, // are we deadass 🥀
            ACTIVE,
            PASSIVE
        };

        /**
         * Constructor for active mode (client socket).
         * The server will connect to the client.
         *
         * @param   clientIp    Client's IP address
         * @param   clientPort  Port provided by client
         */
        DataSocket(const std::string &clientIp, short clientPort);

        /**
         * Constructor for passive mode (server socket).
         * The server listens for an incoming connection.
         */
        DataSocket();

        void acceptConnection();

    private:
        State _state;
    };

}
