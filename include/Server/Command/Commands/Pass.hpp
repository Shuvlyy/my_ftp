#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::command
{

    class Pass final
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
            return "PASS";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "The argument field is a Telnet string specifying the "
                    "user's password. This command must be immediately preceded by the "
                    "user name command, and, for some sites, completes the user's "
                    "identification for access control.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "PASS <password>";
        }
    };

}
