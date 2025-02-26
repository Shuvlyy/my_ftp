#pragma once

#include "User/User.hpp"
#include "Server/Socket/Socket.hpp"
#include "Server/Session/Session.hpp"

#include <unordered_map>

namespace ftp::server::session
{

    class Manager final
    {
    public:
        /**
         * Creates a new session for a user.
         *
         * @param   clientSocket    Client's socket
         * @param   user    Session user
         */
        void createSession(
            const Socket &clientSocket,
            User *user
        );

        /**
         * Closes an active session.
         *
         * @param   clientSocket    Client's socket
         */
        void closeSession(const Socket &clientSocket);

        /**
         * @return  true if client's socket has an active session. Otherwise, false.
         */
        bool hasSession(const Socket &clientSocket) const;

        /**
         * @return  Session associated with the socket
         */
        Session &getSession(const Socket &clientSocket);

        /**
         * @return  User associated with the socket (through the session)
         */
        User *getUser(const Socket &clientSocket);

    private:
        /*                      v Session associated with the Client FD */
        std::unordered_map<int, Session> _sessions;
        /*                 ^ Client FD                                  */
    };

}
