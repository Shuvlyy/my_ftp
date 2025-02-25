#include "Server/Server.hpp"

ftp::Server::Server
(
    const short port,
    const std::string &path
)
    : _isRunning(false),
      _serverSocket(server::Socket(port)),
      _commandManager(server::commands::Manager(this)),
      _sessionManager(server::session::Manager()),
      _userManager(user::Manager(path))
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

    /*while (this->_isRunning) {
        sockaddr_in clientAddr{};
        socklen_t clientAddrLen = sizeof(clientAddr);

        int clientFd = accept(
            this->_serverFd,
            reinterpret_cast<sockaddr *>(&clientAddr),
            &clientAddrLen
        );

        if (clientFd < 0) {
            std::cout << "accept fail" << std::endl;
            throw std::exception(); // TODO: Throw proper exception.
        }

        write(clientFd, "I lost the game :3\n", 19);
        close(clientFd);
    }*/
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
