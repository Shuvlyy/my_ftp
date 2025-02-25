#include "Server/Session/Manager.hpp"

void
ftp::server::session::Manager::createSession
(
    int clientFd,
    const User &user
)
{
    this->_sessions.emplace(clientFd, Session(user));
}

void
ftp::server::session::Manager::closeSession
(
    int clientFd
)
{
    this->_sessions.erase(clientFd);
}

ftp::server::session::Session &
ftp::server::session::Manager::getSession
(
    int clientFd
)
{
    return this->_sessions.at(clientFd);
}
