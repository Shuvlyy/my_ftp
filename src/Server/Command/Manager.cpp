#include "Server/Command/Manager.hpp"

#include "Server/Command/Commands/Help.hpp"

#include "Exception/Exceptions/UnknownCommand.hpp"
#include "Exception/Exceptions/InvalidCommandUsage.hpp"

ftp::server::commands::Manager::Manager
(
    Server *parent
)
    : _parent(parent)
{
    this->registerCommands();
}

std::vector<ftp::server::commands::ICommand *>
ftp::server::commands::Manager::getCommands
()
    const
{
    std::vector<ICommand *> result;

    for (const auto &[_, v] : this->_commands) {
        result.push_back(v.get());
    }
    return result;
}

ftp::server::commands::ICommand *
ftp::server::commands::Manager::getCommand
(
    const std::string &commandName
)
    const
{
    if (!this->_commands.contains(commandName)) {
        return nullptr;
    }
    return this->_commands.at(commandName).get();
}

void
ftp::server::commands::Manager::executeCommand
(
    const std::string &commandName,
    std::vector<std::string> &commandArguments,
    const Socket &clientSocket
)
    const
{
    const auto name = std::string(commandName);

    const ICommand *command = this->getCommand(name);

    if (command == nullptr) {
        throw exception::UnknownCommand(name);
    }

    /* Removing the first element (command name). */
    if (!commandArguments.empty()) {
        commandArguments.erase(commandArguments.begin());
    }

    if (!command->isUsageValid(commandArguments)) {
        throw exception::InvalidCommandUsage(command);
    }

    try {
        command->execute(
            this->_parent,
            commandArguments,
            clientSocket
        );
    }
    catch (exception::IException &exception) {
        std::cout << exception;
    }
}

void
ftp::server::commands::Manager::executeCommand
(
    const std::string &commandName,
    const Socket &clientSocket
)
    const
{
    auto emptyList = std::vector<std::string>();

    this->executeCommand(commandName, emptyList, clientSocket);
}

void
ftp::server::commands::Manager::registerCommands
()
{
    this->registerCommand(std::make_unique<Help>());
}

void
ftp::server::commands::Manager::registerCommand
(
    std::unique_ptr<ICommand> command
)
{
    this->_commands.insert(std::make_pair(
        command->getCommandName(),
        std::move(command)
    ));
}
