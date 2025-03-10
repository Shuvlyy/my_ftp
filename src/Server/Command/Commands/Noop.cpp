#include "Server/Command/Commands/Noop.hpp"

#include "Common/Responses.hpp"

#include <format>

bool
ftp::server::command::Noop::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::command::Noop::execute
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
