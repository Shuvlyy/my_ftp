#include "User/User.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>
#include <utility>

ftp::User::User
(
    std::string username,
    std::string password,
    const std::string &defaultCwd
)
    : _username(std::move(username)),
      _password(std::move(password)),
      _defaultCwd(defaultCwd.empty() ? "" : std::filesystem::canonical(defaultCwd).string())
{}

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
