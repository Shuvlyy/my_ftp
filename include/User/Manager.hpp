#pragma once

#include "User.hpp"

#include <memory>
#include <unordered_map>

namespace ftp::user
{

    class Manager final
    {
    public:
        explicit Manager(const std::string &anonPath);

        User *getUser(const std::string &username) const;

        void registerUser(std::unique_ptr<User> user);

    private:
        std::unordered_map<std::string, std::unique_ptr<User>> _users;

        void registerDefaultUsers(const std::string &anonPath);
    };

}
