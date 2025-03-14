#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/ClientDisconnected.hpp"
#include "Exception/Exceptions/StandardFunctionFail.hpp"
#include "Exception/Exceptions/UnknownCommand.hpp"
#include "Exception/Exceptions/InvalidCommandUsage.hpp"
#include "Exception/Exceptions/UserNotLoggedIn.hpp"
#include "Exception/Exceptions/CouldNotOpenConfig.hpp"

#include <netinet/in.h>

ftp::Server::Server
(
    const unsigned short port,
    const std::string &path,
    const std::string &configPath
)
    : //_dashboard(nullptr),
      _config(yml_create_from_file(configPath.c_str())),
      _commandManager(server::command::Manager(this)),
      _sessionManager(server::session::Manager(this->_config, path)),
      _signalManager(server::signal::Manager(this)),
      _isRunning(false),
      _serverSocket(server::Socket(port))
{
    if (!configPath.empty() && this->_config == nullptr) {
        throw exception::CouldNotOpenConfig();
    }

    this->_maxClients = yml_get_int(this->_config, "settings.maxClients");

    if (this->_maxClients <= 0) {
        this->_maxClients = DEFAULT_MAX_CLIENTS;
    }

    this->_serverSocket.startListening(this->_maxClients);

    this->_pollFds.push_back({
        .fd = this->_serverSocket.getFd(),
        .events = POLLIN,
        .revents = 0
    });
}

ftp::Server::~Server
()
{
    this->terminate();
}

void
ftp::Server::start
()
{
    this->_isRunning = true;

    while (true) {
        // if (this->_dashboard != nullptr) {
        //     this->_dashboard->update();
        // }

        const int ret = poll(
            this->_pollFds.data(),
            this->_pollFds.size(),
            POLL_TIMEOUT
        );

        if (!this->_isRunning) {
            break;
        }

        if (ret < 0) {
            throw exception::StandardFunctionFail("poll");
        }

        for (const pollfd &fd : this->_pollFds) {
            server::Socket clientSocket(fd.fd);

            /* Hmm, not really useful. */
            /*if (fd.revents & POLLHUP) {
                this->disconnectClient(clientSocket, k);
                continue;
            }*/

            if (!(fd.revents & POLLIN)) {
                continue;
            }

            if (fd.fd == this->_serverSocket.getFd()) {
                this->handleNewConnection();
            } else {
                this->handleClientRequest(clientSocket);
            }
        }
    }
}

void
ftp::Server::stop
()
{
    if (!this->_isRunning) {
        return;
    }

    this->_isRunning = false;
    this->_sessionManager.closeAllSessions();
    this->_serverSocket.closeSocket();
}

// void
// ftp::Server::setDashboardInstance
// (
//     Dashboard *dashboard
// )
// {
//     this->_dashboard = dashboard;
// }

yml_t *
ftp::Server::getConfig
()
    const
{
    return this->_config;
}

ftp::Logger &
ftp::Server::getLogger
()
{
    return this->_logger;
}

ftp::server::command::Manager &
ftp::Server::getCommandManager
()
{
    return this->_commandManager;
}

ftp::server::session::Manager &
ftp::Server::getSessionManager
()
{
    return this->_sessionManager;
}

ftp::server::Socket &
ftp::Server::getServerSocket
()
{
    return this->_serverSocket;
}

int
ftp::Server::getMaxClients
()
    const
{
    return this->_maxClients;
}

bool
ftp::Server::isRunning
()
    const
{
    return this->_isRunning;
}

void
ftp::Server::terminate
()
{
    this->stop();
    yml_destroy(this->_config);
}

void
ftp::Server::handleNewConnection
()
{
    sockaddr_in clientAddr {};
    socklen_t clientAddrSize = sizeof(clientAddr);
    const int clientFd = accept(
        this->_serverSocket.getFd(),
        reinterpret_cast<sockaddr *>(&clientAddr),
        &clientAddrSize
    );

    if (clientFd < 0) {
        throw exception::StandardFunctionFail("accept");
    }

    const server::Socket clientSocket(clientFd);

    this->_pollFds.push_back({
        .fd = clientSocket.getFd(),
        .events = POLLIN,
        .revents = 0
    });

    this->_sessionManager.createSession(clientSocket);
    clientSocket.send(RES_SERVICE_READY);
}

static std::vector<std::string>
getCommandArguments
(
    std::string rawCommand
)
{
    std::vector<std::string> tokens;
    size_t pos = 0;

    while ((pos = rawCommand.find(' ')) != std::string::npos) {
        std::string token = rawCommand.substr(0, pos);
        tokens.push_back(token);
        rawCommand.erase(0, pos + 1);
    }

    tokens.push_back(rawCommand);
    return tokens;
}

void
ftp::Server::handleClientRequest
(
    server::Socket &clientSocket
)
{
    try {
        std::string command = clientSocket.receive();

        // command = Utilities::cleanString(command); // R.I.P :(

        if (command.empty()) {
            return;
        }

        std::vector<std::string> arguments = getCommandArguments(command);

        server::Session &session = this->getSessionManager()
            .getSession(clientSocket);

        /* Changes the current working directory to session's working directory. */
        session.cwd(session.getWd());

        try {
            this->_commandManager.executeCommand(
                arguments.at(0),
                arguments,
                clientSocket
            );
        }
        catch (exception::UnknownCommand &) {
            clientSocket.send(RES_SYNTAX_ERROR);
        }
        catch (exception::UserNotLoggedIn &) {
            clientSocket.send(RES_NOT_LOGGED_IN);
        }
        catch (exception::InvalidCommandUsage &) {
            clientSocket.send(RES_SYNTAX_ERROR_PARAMS);
        }
        catch (exception::IException &exception) {
            std::cerr << exception;
        }
    }
    catch (exception::ClientDisconnected &) {
        this->disconnectClient(clientSocket);
    }
    catch (exception::IException &exception) {
        std::cerr << exception;
    }
}

void
ftp::Server::disconnectClient
(
    const server::Socket &clientSocket
)
{
    for (size_t k = 0; k < this->_pollFds.size(); k++) {
        pollfd &fd = this->_pollFds.at(k);

        if (fd.fd == clientSocket.getFd()) {
            this->_pollFds.erase(this->_pollFds.begin() + static_cast<long>(k));
            break;
        }
    }

    this->_sessionManager.closeSession(clientSocket);
}
