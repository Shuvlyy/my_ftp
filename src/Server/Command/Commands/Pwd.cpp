#include "Server/Command/Commands/Pwd.hpp"
#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include <format>

bool
ftp::server::commands::Pwd::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::commands::Pwd::execute
(
    Server *,
    const std::vector<std::string> &,
    Socket &clientSocket,
    Session &session
)
    const
{
    clientSocket.send(std::format(RES_PATH_CREATED, session.getWd()));
}
