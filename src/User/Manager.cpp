#include "User/Manager.hpp"

ftp::user::Manager::Manager
(
    const std::string &anonPath
)
{
    this->registerDefaultUsers(anonPath);
}

ftp::User *
ftp::user::Manager::getUser
(
    const std::string &username
)
    const
{
    if (!this->_users.contains(username)) {
        return nullptr;
    }
    return this->_users.at(username).get();
}

void
ftp::user::Manager::registerUser
(
    std::unique_ptr<User> user
)
{
    this->_users.insert(std::make_pair(
        user->getUsername(),
        std::move(user)
    ));
}

void
ftp::user::Manager::registerDefaultUsers
(
    const std::string &anonPath
)
{
    this->registerUser(std::make_unique<User>(anonPath));
}
