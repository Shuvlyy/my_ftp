#include "Server/Command/Commands/Quit.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::commands::Quit::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::commands::Quit::execute
(
    Server *server,
    const std::vector<std::string> &,
    Socket &clientSocket,
    Session &
)
    const
{
    clientSocket.send(RES_SERVICE_CLOSING);
    clientSocket.send(RES_COMMAND_OK);
    server->disconnectClient(clientSocket);
}
