#include "Server/Session/Manager.hpp"

void
ftp::server::session::Manager::createSession
(
    const Socket &clientSocket,
    User *user
)
{
    if (this->hasSession(clientSocket)) {
        return; // TODO: Maybe throw exception
    }

    this->_sessions.emplace(
        clientSocket.getFd(),
        Session(user)
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
