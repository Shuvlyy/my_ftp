#include "User/User.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>
#include <iostream>
#include <utility>

ftp::User::User
(
    std::string username,
    std::string password,
    const std::string &defaultWd
)
    : _username(std::move(username)),
      _password(std::move(password))
{
    if (!defaultWd.empty()) {
        try {
            this->_defaultWd = std::filesystem::canonical(defaultWd).string();
        }
        catch (const std::exception &) {
            std::cerr << "Warning while creating user \"" << this->_username << "\":" << std::endl;
            std::cerr << "Could not open folder \"" << defaultWd << "\". Setting root to current path." << std::endl;
            this->_defaultWd = std::filesystem::current_path();
        }
    }
}

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
