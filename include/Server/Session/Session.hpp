#pragma once

#include "User/User.hpp"

namespace ftp::server
{

    class Session final
    {
    public:
        explicit Session(int fd);
        explicit Session(int fd, User *user);

        /**
         * Logs the user in (the user associated with the session).
         *
         * @param   password    Password
         * @return  true        if login is successful
         * @return  false       if login isn't successful
         */
        bool login(const std::string &password);

        void cwd(const std::string &path);

        [[nodiscard]] User *getUser() const;
        [[nodiscard]] bool isLoggedIn() const;
        [[nodiscard]] std::string getWd() const;

        void setUser(User *user);

    private:
        int _fd;
        User *_user;
        bool _isLoggedIn;
        std::string _wd;
    };

}
