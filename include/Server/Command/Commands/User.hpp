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
            return "USER";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "The argument field is a Telnet string "
                    "identifying the user. The user identification is that which is required by the "
                    "server for access to its file system. This command will "
                    "normally be the first command transmitted by the user after "
                    "the control connections are made (some servers may require "
                    "this).";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "USER <username>";
        }
    };

}
