#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/ClientDisconnected.hpp"
#include "Exception/Exceptions/StandardFunctionFail.hpp"
#include "Exception/Exceptions/UnknownCommand.hpp"
#include "Exception/Exceptions/InvalidCommandUsage.hpp"

#include <fcntl.h>
#include <netinet/in.h>

ftp::Server::Server
(
    const short port,
    const std::string &path
)
    : _isRunning(false),
      _serverSocket(server::Socket(port)),
      _commandManager(server::commands::Manager(this)),
      _userManager(user::Manager(path)),
      _sessionManager(server::session::Manager())
{
    this->_serverSocket.startListening();
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

    this->_pollFds.push_back({
        .fd = this->_serverSocket.getFd(),
        .events = POLLIN,
        .revents = 0
    });

    while (this->_isRunning) {
        const int ret = poll(
            this->_pollFds.data(),
            this->_pollFds.size(),
            POLL_TIMEOUT
        );

        if (ret < 0) {
            // TODO: poll fail, throw proper exception
            return;
        }

        for (size_t k = 0; k < this->_pollFds.size(); ++k) {
            pollfd &fd = this->_pollFds.at(k);
            server::Socket clientSocket(fd.fd);

            if (fd.revents & POLLHUP) {
                this->disconnectClient(clientSocket, k);
                continue;
            }

            if (!(fd.revents & POLLIN)) {
                continue;
            }

            if (fd.fd == this->_serverSocket.getFd()) {
                this->handleNewConnection();
            } else {
                this->handleClientRequest(clientSocket, k);
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
    this->_serverSocket.closeSocket();
}

ftp::server::commands::Manager &
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

ftp::user::Manager &
ftp::Server::getUserManager
()
{
    return this->_userManager;
}

void
ftp::Server::terminate
()
{
    this->stop();
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

    this->_sessionManager.createSession(
        clientSocket,
        this->getUserManager().getUser(USER_ANONYMOUS_NAME) // FIXME: Nearly a magic value.
    );
    clientSocket.send(RES_SERVICE_READY);
}

static bool
shouldBufferBeIgnored
(
    const std::string &buffer
)
{
    if (buffer.empty()) {
        return true;
    }

    for (const char it : buffer) {
        if (it != ' ' && it != '\t') {
            return false;
        }
    }
    return true;
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
    server::Socket &clientSocket,
    size_t index
)
{

    try {
        std::string command = clientSocket.receive();

        if (shouldBufferBeIgnored(command)) {
            return;
        }

        std::vector<std::string> arguments = getCommandArguments(command);

        try {
            this->_commandManager.executeCommand(
                arguments.at(0),
                arguments,
                clientSocket
            );

            clientSocket.send(RES_COMMAND_OK);
        }
        catch (exception::UnknownCommand &exception) {
            clientSocket.send(RES_SYNTAX_ERROR);
        }
        catch (exception::InvalidCommandUsage &exception) {
            clientSocket.send(RES_SYNTAX_ERROR_PARAMS);
        }
        catch (exception::IException &exception) {
            std::cout << exception;
        }
    }
    catch (exception::ClientDisconnected &) {
        this->disconnectClient(clientSocket, index);
    }
    catch (exception::IException &exception) {
        std::cout << exception;
    }
}

void
ftp::Server::disconnectClient
(
    server::Socket &clientSocket,
    size_t index
)
{
    clientSocket.closeSocket();
    this->_pollFds.erase(this->_pollFds.begin() + static_cast<long>(index));
    this->_sessionManager.closeSession(clientSocket);
}
