#pragma once

#include "User/User.hpp"

#include <unordered_map>

namespace ftp::server::session
{

    struct Session
    {
        User user;
        bool isAuthenticated;

        explicit Session(const User &user)
            : user(user), isAuthenticated(false)
        {}
    };

    class Manager final
    {
    public:
        /**
         * Creates a new session for a user.
         *
         * @param   clientFd    File descriptor of the client
         * @param   user
         */
        void createSession(
            int clientFd,
            const User &user
        );

        /**
         * Closes an active session.
         *
         * @param   clientFd    File descriptor of the client
         */
        void closeSession(int clientFd);

        /**
         * @return  Session associated with the file descriptor
         */
        Session &getSession(int clientFd);

    private:
        std::unordered_map<int, Session> _sessions;
    };

}
