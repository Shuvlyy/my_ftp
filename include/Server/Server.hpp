#pragma once

#include "Command/Manager.hpp"
#include "Session/Manager.hpp"
#include "User/Manager.hpp"

#include <string>
#include <vector>

#include <sys/poll.h>

namespace ftp
{

    class Server final
    {
    public:
        explicit Server(
            short port,
            const std::string &path
        );
        ~Server();

        void start();
        void stop();

        [[nodiscard]] server::commands::Manager &getCommandManager();
        [[nodiscard]] server::session::Manager &getSessionManager();
        [[nodiscard]] user::Manager &getUserManager();

    private:
        bool _isRunning;
        server::Socket _serverSocket;
        server::commands::Manager _commandManager;
        server::session::Manager _sessionManager;
        user::Manager _userManager;
        std::vector<pollfd> _pollFds;

        void initialize();
        void terminate();
        void handleNewConnection();
        void handleClientRequest(size_t index);
    };

}
