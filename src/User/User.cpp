#include "User/User.hpp"

#include <utility>

ftp::User::User
(
    std::string username,
    std::string password,
    std::string defaultCwd
)
    : _username(std::move(username)),
      _password(std::move(password)),
      _defaultCwd(std::move(defaultCwd))
{
}

ftp::User::User
(
    const std::string &defaultCwd
)
    : User(
        USER_ANONYMOUS_NAME,
        USER_ANONYMOUS_PASSWORD,
        defaultCwd
    )
{}

std::string
ftp::User::getUsername
()
const
{
    return _username;
}

std::string
ftp::User::getPassword
()
    const
{
    return _password;
}

std::string
ftp::User::getDefaultCwd
()
const
{
    return _defaultCwd;
}
