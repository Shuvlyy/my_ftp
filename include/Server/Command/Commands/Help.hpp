#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::command
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

        [[nodiscard]] std::string getCommandName()
            const override
        {
            return "HELP";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "This command shall cause the server to send helpful "
                    "information regarding its implementation status over the "
                    "control connection to the user.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "HELP [<command>]";
        }

    private:
        static void displayCommandHelp(
            Server *server,
            const std::string &commandName,
            const Socket &clientSocket
        );
    };

}
