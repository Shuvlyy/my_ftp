#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::command
{

    class Mkd final
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
            return "MKD";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "MKD <dirname>";
        }
    };

}
