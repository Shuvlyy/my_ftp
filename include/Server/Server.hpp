#pragma once

#define POLL_TIMEOUT (-1)

#include "Command/Manager.hpp"
#include "Session/Manager.hpp"
#include "Signal/Manager.hpp"
#include "Logger/Logger.hpp"

#include <string>
#include <vector>

#include <sys/poll.h>

namespace ftp
{

    class Server final
    {
    public:
        explicit Server(
            unsigned short port,
            const std::string &path
        );
        ~Server();

        void start();
        void stop();

        void disconnectClient(
            const server::Socket &clientSocket
        );

        [[nodiscard]] server::command::Manager &getCommandManager();
        [[nodiscard]] server::session::Manager &getSessionManager();

    private:
        Logger _logger;
        server::command::Manager _commandManager;
        server::session::Manager _sessionManager;
        server::sig::Manager _signalManager;
        bool _isRunning;
        server::Socket _serverSocket;
        std::vector<pollfd> _pollFds;

        void terminate();
        void handleNewConnection();
        void handleClientRequest(server::Socket &clientSocket);
    };

}
