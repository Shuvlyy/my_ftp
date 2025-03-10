#include "Server/Session/Session.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"
#include "Exception/Exceptions/UserNotLoggedIn.hpp"
#include "Exception/Exceptions/WdOutOfScope.hpp"
#include "Exception/Exceptions/PathIsNotDir.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>
#include <unistd.h>

ftp::server::Session::Session
(
    const int fd,
    User *user
)
    : _controlSocket(Socket(fd)),
      _dataSocket(DataSocket('J')), // 'J' is magic value, has no impact.
      _user(user),
      _isLoggedIn(false)
{}

ftp::server::Session::Session
(
    const int fd
)
    : Session(fd, nullptr)
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

    if (this->_user->getUsername() == USER_UNKNOWN_NAME) {
        return false;
    }

    if (password == this->_user->getPassword()) {
        this->_isLoggedIn = true;
        this->_wd = std::string(this->_user->getDefaultCwd());
    }

    return this->_isLoggedIn;
}

void
ftp::server::Session::cwd
(
    const std::string &path
)
{
    if (path.empty()) {
        return;
    }

    if (!this->_isLoggedIn) {
        throw exception::UserNotLoggedIn(this->_controlSocket.getFd());
    }

    const std::string absolutePath = Utilities::getAbsolutePath(this->_wd, path);

    if (this->getWd() == absolutePath) {
        return;
    }

    if (!std::filesystem::is_directory(absolutePath)) {
        throw exception::PathIsNotDir(absolutePath);
    }

    if (!absolutePath.starts_with(this->_user->getDefaultCwd())) {
        throw exception::WdOutOfScope(absolutePath);
    }

    if (chdir(absolutePath.c_str()) != 0) {
        throw exception::StandardFunctionFail("chdir");
    }

    this->_wd = std::filesystem::current_path();
}

ftp::server::Socket &
ftp::server::Session::getControlSocket
()
{
    return this->_controlSocket;
}

ftp::server::DataSocket &
ftp::server::Session::getDataSocket
()
{
    return this->_dataSocket;
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

std::string
ftp::server::Session::getWd
()
    const
{
    return this->_wd;
}

void
ftp::server::Session::setUser
(
    User *user
)
{
    this->_isLoggedIn = false;
    this->_user = user;
}
