#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class User final
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
            return "user";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "hlp meow.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "user [username]";
        }

    private:
        static void displayCommandHelp(
            Server *shell,
            const std::string &commandName
        );
    };

}