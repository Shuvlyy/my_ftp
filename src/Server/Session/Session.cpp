#include "Server/Session/Session.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <filesystem>
#include <unistd.h>

ftp::server::Session::Session
(
    User *user
)
    : _user(user),
      _isLoggedIn(false)
{}

ftp::server::Session::Session
()
    : Session(nullptr)
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
        // TODO: Throw proper exception (UserNotLoggedIn)
        return;
    }

    const std::string absolutePath = std::filesystem::weakly_canonical(path);

    if (!std::filesystem::is_directory(absolutePath)) {
        // TODO: Throw proper exception (PathIsNotDir)
        return;
    }

    if (!absolutePath.starts_with(this->_user->getDefaultCwd())) {
        // TODO: Throw proper exception (DirOutOfScope) (no permission)
        return;
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
