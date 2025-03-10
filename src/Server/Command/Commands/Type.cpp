#include "Server/Command/Commands/Type.hpp"

#include "Common/Responses.hpp"

#include <format>

bool
ftp::server::command::Type::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::Type::execute
(
    Server *,
    const std::vector<std::string> &,
    Socket &clientSocket,
    Session &
)
    const
{
    clientSocket.send(std::format(RES_COMMAND_OK, this->getCommandName()));
}
