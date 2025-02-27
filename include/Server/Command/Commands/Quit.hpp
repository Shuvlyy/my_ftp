#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Quit final
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
            return "QUIT";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "This command terminates a USER and if file transfer "
                     "is not in progress, the server closes the control connection.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "QUIT";
        }
    };

}
