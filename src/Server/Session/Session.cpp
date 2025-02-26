#include "Server/Session/Session.hpp"

ftp::server::Session::Session
(
    User *user
)
    : _user(user),
      _isLoggedIn(false)
{}

bool
ftp::server::Session::login
(
    const std::string &password
)
{
    if (this->_user == nullptr) {
        return false;
    }

    if (password == this->_user->getPassword()) {
        this->_isLoggedIn = true;
    }

    return this->_isLoggedIn;
}

ftp::User *
ftp::server::Session::getUser
()
    const
{
    return this->_user;
}

bool
ftp::server::Session::isLoggedIn
()
    const
{
    return this->_isLoggedIn;
}