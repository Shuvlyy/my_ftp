#pragma once

#include "User/User.hpp"

namespace ftp::server
{

    class Session final
    {
    public:
        explicit Session();
        explicit Session(User *user);

        /**
         * Logs the user in (the user associated with the session).
         *
         * @param   password        Password
         * @return  true            if login is successful
         * @return  false           if login isn't successful
         */
        bool login(const std::string &password);

        [[nodiscard]] User *getUser() const;
        [[nodiscard]] bool isLoggedIn() const;

        void setUser(User *user);

    private:
        User *_user;
        bool _isLoggedIn;
    };

}
