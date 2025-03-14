#include "Server/Command/Commands/User.hpp"
#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::command::User::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::User::execute
(
    Server *server,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    if (session.isLoggedIn()) {
        clientSocket.send(RES_BAD_COMMAND_SEQUENCE);
        return;
    }

    const std::string &targetUsername = commandArguments.at(0);

    ftp::User *user = server->getSessionManager().getUserManager()
        .getUser(targetUsername);

    /* If user is not found, then put an inaccessible one. */
    if (user == nullptr) {
        user = server->getSessionManager().getUserManager()
            .getUser(USER_UNKNOWN_NAME);
    }

    session.setUser(user);

    clientSocket.send(RES_USER_OK_NEED_PASSWORD);
}
