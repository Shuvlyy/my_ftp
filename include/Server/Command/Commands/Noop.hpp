#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Noop final
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
            return "NOOP";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "This command does not affect any parameters or previously "
                     "entered commands. It specifies no action other than that the "
                     "server send an OK reply.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "NOOP";
        }
    };

}
