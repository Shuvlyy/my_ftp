#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::command
{

    class Pwd final
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
            return "PWD";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "This command causes the name of the current working "
                    "directory to be returned in the reply.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "PWD";
        }
    };

}
