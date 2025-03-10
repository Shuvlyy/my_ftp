#pragma once

#include "Exception/AException.hpp"

namespace ftp::exception
{

    class InvalidCommandUsage final
        : public AException
    {
    public:
        explicit InvalidCommandUsage(
            const std::string &commandName,
            const std::string &commandSyntax
        )
            : AException(commandName + ": Invalid command usage.\n"
                         "Correct usage: " + commandSyntax)
        {}

        explicit InvalidCommandUsage(
            const server::command::ICommand *command
        )
            : InvalidCommandUsage(
                command->getCommandName(),
                command->getCommandSyntax()
            )
        {}
    };

}
