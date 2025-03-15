#include "Server/Command/Manager.hpp"

#include "Common/Responses.hpp"

#include "Server/Server.hpp"

#include "Server/Session/Session.hpp"

#include "Server/Command/Commands/Help.hpp"
#include "Server/Command/Commands/User.hpp"
#include "Server/Command/Commands/Pass.hpp"
#include "Server/Command/Commands/Noop.hpp"
#include "Server/Command/Commands/Quit.hpp"
#include "Server/Command/Commands/Cwd.hpp"
#include "Server/Command/Commands/Pwd.hpp"
#include "Server/Command/Commands/Cdup.hpp"
#include "Server/Command/Commands/Dele.hpp"
#include "Server/Command/Commands/Port.hpp"
#include "Server/Command/Commands/Pasv.hpp"
#include "Server/Command/Commands/List.hpp"
#include "Server/Command/Commands/Type.hpp"
#include "Server/Command/Commands/Stor.hpp"
#include "Server/Command/Commands/Retr.hpp"
#include "Server/Command/Commands/Mkd.hpp"
#include "Server/Command/Commands/Rmd.hpp"

#include "Exception/Exceptions/UnknownCommand.hpp"
#include "Exception/Exceptions/InvalidCommandUsage.hpp"
#include "Exception/Exceptions/UserNotLoggedIn.hpp"

#include "Utilities/Utilities.hpp"

ftp::server::command::Manager::Manager
(
    Server *parent
)
    : _parent(parent)
{
    this->registerCommands();
}

std::vector<ftp::server::command::ICommand *>
ftp::server::command::Manager::getCommands
()
    const
{
    std::vector<ICommand *> result;

    for (const auto &[_, v] : this->_commands) {
        result.push_back(v.get());
    }
    return result;
}

ftp::server::command::ICommand *
ftp::server::command::Manager::getCommand
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
ftp::server::command::Manager::executeCommand
(
    const std::string &commandName,
    std::vector<std::string> &commandArguments,
    Socket &clientSocket
)
    const
{
    const std::string name = Utilities::stringToUpper(commandName);

    const ICommand *command = this->getCommand(name);

    if (command == nullptr) {
        throw exception::UnknownCommand(name);
    }

    /* Removing the first element (command name). */
    if (!commandArguments.empty()) {
        commandArguments.erase(commandArguments.begin());
    }

    Session &session = this->_parent->getSessionManager()
        .getSession(clientSocket);

    if (command->doesNeedLogin() && !session.isLoggedIn()) {
        throw exception::UserNotLoggedIn(clientSocket.getFd());
    }

    if (!command->isUsageValid(commandArguments)) {
        throw exception::InvalidCommandUsage(command);
    }

    try {
        command->execute(
            this->_parent,
            commandArguments,
            clientSocket,
            session
        );
    }
    catch (exception::IException &exception) {
        std::cerr << exception;
        session.getControlSocket().send(RES_UNKNOWN);
    }
}

void
ftp::server::command::Manager::executeCommand
(
    const std::string &commandName,
    Socket &clientSocket
)
    const
{
    auto emptyList = std::vector<std::string>();

    this->executeCommand(commandName, emptyList, clientSocket);
}

void
ftp::server::command::Manager::registerCommands
()
{
    this->registerCommand(std::make_unique<Help>());
    this->registerCommand(std::make_unique<User>());
    this->registerCommand(std::make_unique<Pass>());
    this->registerCommand(std::make_unique<Noop>());
    this->registerCommand(std::make_unique<Quit>());
    this->registerCommand(std::make_unique<Cwd>());
    this->registerCommand(std::make_unique<Pwd>());
    this->registerCommand(std::make_unique<Cdup>());
    this->registerCommand(std::make_unique<Dele>());
    this->registerCommand(std::make_unique<Port>());
    this->registerCommand(std::make_unique<Pasv>());
    this->registerCommand(std::make_unique<List>());
    this->registerCommand(std::make_unique<Type>());
    this->registerCommand(std::make_unique<Stor>());
    this->registerCommand(std::make_unique<Retr>());
    this->registerCommand(std::make_unique<Mkd>());
    this->registerCommand(std::make_unique<Rmd>());
}

void
ftp::server::command::Manager::registerCommand
(
    std::unique_ptr<ICommand> command
)
{
    this->_commands.insert(std::make_pair(
        command->getCommandName(),
        std::move(command)
    ));
}
