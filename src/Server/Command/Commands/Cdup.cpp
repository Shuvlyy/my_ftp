#include "Server/Command/Commands/Cdup.hpp"

#include "Exception/Exceptions/WdOutOfScope.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include <format>

bool
ftp::server::commands::Cdup::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::commands::Cdup::execute
(
    Server *,
    const std::vector<std::string> &,
    Socket &clientSocket,
    Session &session
)
    const
{
    try {
        session.cwd("..");
        clientSocket.send(std::format(RES_COMMAND_OK, this->getCommandName()));
    }
    catch (exception::WdOutOfScope &exception) {
        clientSocket.send("out of scope (no permission)!!");
    }
}
