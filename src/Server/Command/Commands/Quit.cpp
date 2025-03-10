#include "Server/Command/Commands/Quit.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::command::Quit::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::command::Quit::execute
(
    Server *server,
    const std::vector<std::string> &,
    Socket &clientSocket,
    Session &
)
    const
{
    clientSocket.send(RES_SERVICE_CLOSING);
    server->disconnectClient(clientSocket);
}
