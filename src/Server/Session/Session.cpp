#include "Server/Session/Session.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"
#include "Exception/Exceptions/UserNotLoggedIn.hpp"
#include "Exception/Exceptions/WdOutOfScope.hpp"
#include "Exception/Exceptions/PathIsNotDir.hpp"

#include <filesystem>
#include <unistd.h>

ftp::server::Session::Session
(
    const int fd,
    User *user
)
    : _fd(fd),
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
    if (!this->_isLoggedIn || path.empty()) {
        return;
    }

    const std::string absolutePath = std::filesystem::weakly_canonical(path);

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
