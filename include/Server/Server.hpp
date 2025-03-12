#pragma once

#define POLL_TIMEOUT (-1)

#include "Command/Manager.hpp"
#include "Session/Manager.hpp"
#include "Signal/Manager.hpp"
#include "Logger/Logger.hpp"
// #include "Dashboard/Dashboard.hpp"

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

        // void setDashboardInstance(Dashboard *dashboard);

        [[nodiscard]] Logger &getLogger();
        [[nodiscard]] server::command::Manager &getCommandManager();
        [[nodiscard]] server::session::Manager &getSessionManager();
        [[nodiscard]] server::Socket &getServerSocket();
        [[nodiscard]] bool isRunning() const;

    private:
        Logger _logger;
        // Dashboard *_dashboard;
        server::command::Manager _commandManager;
        server::session::Manager _sessionManager;
        server::signal::Manager _signalManager;
        bool _isRunning;
        server::Socket _serverSocket;
        std::vector<pollfd> _pollFds;

        void terminate();
        void handleNewConnection();
        void handleClientRequest(server::Socket &clientSocket);
    };

}
