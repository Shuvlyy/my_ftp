#include "User/Manager.hpp"

#include "../../yml_parser/shuvlib/include/shuvlib/array.h"

ftp::user::Manager::Manager
(
    yml_t *config,
    const std::string &anonPath
)
{
    this->registerDefaultUsers(config, anonPath);
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
    yml_t *config,
    const std::string &anonPath
)
{
    this->registerUser(std::make_unique<User>(USER_UNKNOWN_NAME, "", ""));

    if (config == nullptr) { // Just in case lmao
        this->registerUser(std::make_unique<User>(anonPath));
        return;
    }

    if (yml_get_bool(config, "settings.allowAnonymousUser")) {
        this->registerUser(std::make_unique<User>(anonPath));
    }

    char **users = yml_get_list(config, "users");

    for (int k = 0; users[k] != nullptr; k++) {
        std::string username = users[k];
        const char* passwordCStr = yml_get_str(config, ("users." + username + ".password").c_str());
        const char* rootPathCStr = yml_get_str(config, ("users." + username + ".root").c_str());

        std::string password = passwordCStr ? std::string(passwordCStr) : "";
        std::string defaultWd = rootPathCStr ? std::string(rootPathCStr) : "";

        this->registerUser(std::make_unique<User>(username, password, defaultWd));
    }

    sh_destroy_string_array(users);

    if (yml_get_bool(config, "settings.registerUsersInMyFtpGroup")) {
        // TODO: Do this lol
    }
}
