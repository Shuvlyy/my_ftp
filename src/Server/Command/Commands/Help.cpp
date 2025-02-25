#include "Server/Command/Commands/Help.hpp"
#include "Server/Server.hpp"
#include "Exception/Exceptions/UnknownCommand.hpp"

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
    const Socket &
)
    const
{
    if (commandArguments.empty()) { // General help
        const std::vector<ICommand *> commands = server->getCommandManager().getCommands();

        for (const auto &command : commands) {
            std::cout << "- " << command->getCommandName() << ": " << command->getCommandDescription() << std::endl;
        }
        return;
    }

    displayCommandHelp(server, commandArguments.at(0));
}

void
ftp::server::commands::Help::displayCommandHelp
(
    Server *server,
    const std::string &commandName
)
{
    const ICommand *command = server->getCommandManager().getCommand(commandName);

    if (command == nullptr) {
        throw exception::UnknownCommand(commandName);
    }

    std::cout << "NAME" << std::endl;
    std::cout << "\t" << command->getCommandName() << std::endl;
    std::cout << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\t" << command->getCommandDescription() << std::endl;
    std::cout << std::endl;
    std::cout << "USAGE" << std::endl;
    std::cout << "\t" << command->getCommandSyntax() << std::endl;
}