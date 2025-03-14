#include "Server/Session/Manager.hpp"

#include <iostream>

ftp::server::session::Manager::Manager
(
    yml_t *config,
    const std::string &anonPath
)
    : _userManager(user::Manager(config, anonPath))
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
    const int socketFd,
    Session &session
)
{
    session.getControlSocket().closeSocket();
    session.getDataSocket().closeSocket();
    this->_sessions.erase(socketFd);
}

void
ftp::server::session::Manager::closeSession
(
    const Socket &clientSocket
)
{
    const int socketFd = clientSocket.getFd();
    Session &session = this->_sessions.at(socketFd);

    this->closeSession(socketFd, session);
}

void
ftp::server::session::Manager::closeAllSessions
()
{
    for (auto &[fd, session] : this->_sessions) {
        session.getDataSocket().closeSocket();
        session.getControlSocket().closeSocket();
    }
    this->_sessions.clear();
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

std::vector<ftp::server::Session *>
ftp::server::session::Manager::getSessions
()
{
    std::vector<Session *> result;

    for (auto &[_, session] : this->_sessions) {
        result.push_back(&session);
    }
    return result;
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
