#include "Server/Command/Commands/Port.hpp"

#include "Server/Server.hpp"

bool
ftp::server::commands::Port::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::commands::Port::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    // ...
    clientSocket.send("Executed");
}
