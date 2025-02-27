#include "Server/Command/Commands/Help.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Utilities/Utilities.hpp"

bool
ftp::server::commands::Help::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() <= 1;
}

void
ftp::server::commands::Help::execute
(
    Server *server,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &
)
    const
{
    if (commandArguments.empty()) {
        clientSocket.send(RES_HELP);
        return;
    }

    displayCommandHelp(
        server,
        commandArguments.at(0),
        clientSocket
    );
}

void
ftp::server::commands::Help::displayCommandHelp
(
    Server *server,
    const std::string &commandName,
    const Socket &clientSocket
)
{
    const ICommand *command = server->getCommandManager()
        .getCommand(Utilities::stringToUpper(commandName));

    if (command == nullptr) {
        clientSocket.send(RES_SYNTAX_ERROR);
        return;
        // throw exception::UnknownCommand(commandName); // :(
    }

    const std::string output("214 - " + command->getCommandDescription());

    clientSocket.send(output);
}
