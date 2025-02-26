#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Help final
        : public ACommand
    {
    public:
        [[nodiscard]] bool isUsageValid(
            const std::vector<std::string> &commandArguments
        ) const override;

        void execute(
            Server *server,
            const std::vector<std::string> &commandArguments,
            Socket &clientSocket,
            Session &session
        ) const override;

        [[nodiscard]] bool
        doesNeedLogin()
            const override
        {
            return false;
        }

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
            Server *server,
            const std::string &commandName
        );
    };

}