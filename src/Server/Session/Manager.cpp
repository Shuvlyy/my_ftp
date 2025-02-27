#include "Server/Session/Manager.hpp"

ftp::server::session::Manager::Manager
(
    const std::string &anonPath
)
    : _userManager(user::Manager(anonPath))
{}

void
ftp::server::session::Manager::createSession
(
    const Socket &clientSocket
)
{
    if (this->hasSession(clientSocket)) {
        return;
    }

    const int clientFd = clientSocket.getFd();

    this->_sessions.emplace(
        clientFd,
        Session(clientFd)
    );
}

void
ftp::server::session::Manager::closeSession
(
    const Socket &clientSocket
)
{
    this->_sessions.erase(clientSocket.getFd());
}

bool
ftp::server::session::Manager::hasSession
(
    const Socket &clientSocket
)
    const
{
    return this->_sessions.contains(clientSocket.getFd());
}

ftp::server::Session &
ftp::server::session::Manager::getSession
(
    const Socket &clientSocket
)
{
    return this->_sessions.find(clientSocket.getFd())->second;
}

ftp::User *
ftp::server::session::Manager::getUser
(
    const Socket &clientSocket
)
{
    if (!this->hasSession(clientSocket)) {
        return nullptr;
    }
    return this->getSession(clientSocket).getUser();
}

void
ftp::server::session::Manager::setUser
(
    const Socket &clientSocket,
    const std::string &username
)
{
    Session &session = this->getSession(clientSocket);
    User *user = this->getUserManager().getUser(username);

    if (user == nullptr) {
        // TODO: Throw exception (usernotfound)
        return;
    }

    session.setUser(user);
}

ftp::user::Manager &
ftp::server::session::Manager::getUserManager
()
{
    return this->_userManager;
}
