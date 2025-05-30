#pragma once

#include "User/User.hpp"
#include "User/Manager.hpp"
#include "Server/Socket/Socket.hpp"
#include "Server/Session/Session.hpp"

#include <vector>
#include <unordered_map>

namespace ftp::server::session
{

    class Manager final
    {
    public:
        explicit Manager(yml_t *config, const std::string &anonPath);

        /**
         * Creates a new session for a user.
         *
         * @param   clientSocket    Client's socket
         */
        void createSession(const Socket &clientSocket);

        /**
         * Closes an active session.
         *
         * @param   socketFd    File descriptor of the socket of the session to close
         * @param   session     Session to close
         */
        void closeSession(int socketFd, Session &session);

        /**
         * Closes an active session.
         *
         * @param   clientSocket    Client's socket
         */
        void closeSession(const Socket &clientSocket);

        /**
         * Closes all active sessions.
         */
        void closeAllSessions();

        /**
         * @return  true if client's socket has an active session. Otherwise, false.
         */
        bool hasSession(const Socket &clientSocket) const;

        std::vector<Session *> getSessions();

        /**
         * @return  Session associated with the socket
         */
        Session &getSession(const Socket &clientSocket);

        /**
         * @return  User associated with the socket (through the session)
         */
        User *getUser(const Socket &clientSocket);

        void setUser(
            const Socket &clientSocket,
            const std::string &username
        );

        [[nodiscard]] user::Manager &getUserManager();

    private:
        user::Manager _userManager;

        /*                      v Session associated with the Client FD */
        std::unordered_map<int, Session> _sessions;
        /*                 ^ Client FD                                  */
    };

}
