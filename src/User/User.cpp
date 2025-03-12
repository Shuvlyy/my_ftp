#include "User/User.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>
#include <utility>

ftp::User::User
(
    std::string username,
    std::string password,
    const std::string &defaultWd
)
    : _username(std::move(username)),
      _password(std::move(password)),
      _defaultWd(defaultWd.empty() ? "" : std::filesystem::canonical(defaultWd).string())
{}

ftp::User::User
(
    const std::string &defaultWd
)
    : User(
        USER_ANONYMOUS_NAME,
        USER_ANONYMOUS_PASSWORD,
        defaultWd
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
ftp::User::getDefaultWd
()
const
{
    return _defaultWd;
}
