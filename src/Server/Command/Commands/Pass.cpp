#include "Server/Command/Commands/Pass.hpp"
#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::commands::Pass::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() <= 1;
}

void
ftp::server::commands::Pass::execute
(
    Server *server,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    std::string password;

    if (commandArguments.size() == 1) {
        password = commandArguments.at(0);
    }

    if (session.getUser() == nullptr) {
        clientSocket.send(RES_NEED_ACCOUNT);
        return;
    }

    if (session.isLoggedIn()) {
        clientSocket.send("already logged in");
    }

    if (!session.login(password)) {
        clientSocket.send("wrong password");
        return;
    }

    clientSocket.send(RES_USER_LOGGED_IN);
}
