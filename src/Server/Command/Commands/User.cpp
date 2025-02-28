#include "Server/Command/Commands/User.hpp"
#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::commands::User::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::commands::User::execute
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

    ftp::User *user = server->getSessionManager().getUserManager()
        .getUser(commandArguments.at(0));

    if (user == nullptr) {
        clientSocket.send(RES_NOT_LOGGED_IN);
        return;
    }

    session.setUser(user);

    if (user->getPassword().empty()) {
        session.login("");
        clientSocket.send(RES_USER_LOGGED_IN);
        return;
    }

    clientSocket.send(RES_USER_OK_NEED_PASSWORD);
}
