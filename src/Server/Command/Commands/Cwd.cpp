#include "Server/Command/Commands/Cwd.hpp"
#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::commands::Cwd::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::commands::Cwd::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    session.cwd(commandArguments.at(0));
    clientSocket.send(RES_FILE_ACTION_REQ);
}
