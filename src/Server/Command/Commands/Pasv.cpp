#include "Server/Command/Commands/Pasv.hpp"

#include "Server/Server.hpp"

bool
ftp::server::commands::Pasv::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::commands::Pasv::execute
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
