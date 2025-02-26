#pragma once

#include "User/User.hpp"

namespace ftp::server
{

    class Session final
    {
    public:
        explicit Session(User *user);

        /**
         * Logs the user in (the user associated with the session).
         *
         * @param   password        Password
         */
        bool login(const std::string &password);

        [[nodiscard]] User *getUser() const;
        [[nodiscard]] bool isLoggedIn() const;

    private:
        User *_user;
        bool _isLoggedIn;
    };

}
