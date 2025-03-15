#pragma once

#include "User.hpp"

#include "yml.h"

#include <memory>
#include <unordered_map>
#include <vector>

namespace ftp::user
{

    class Manager final
    {
    public:
        explicit Manager(yml_t *config, const std::string &anonPath);

        void registerUser(std::unique_ptr<User> user);

        std::vector<User *> getRegisteredUsers() const;
        User *getUser(const std::string &username) const;

    private:
        std::unordered_map<std::string, std::unique_ptr<User>> _users;

        void registerDefaultUsers(yml_t *config, const std::string &anonPath);
    };

}
