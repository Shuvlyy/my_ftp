#pragma once

#include "Server/Command/ICommand.hpp"

namespace ftp::server::commands
{

    class Help final
        : public ICommand
    {
    public:
        [[nodiscard]] bool isUsageValid(
            const std::vector<std::string> &commandArguments
        ) const override;

        void execute(
            Server *shell,
            const std::vector<std::string> &commandArguments,
            const Socket &clientSocket
        ) const override;

        [[nodiscard]] std::string getCommandName()
            const override
        {
            return "help";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "Prints out the help about every or a specific command.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "help [command]";
        }

    private:
        static void displayCommandHelp(
            Server *shell,
            const std::string &commandName
        );
    };

}