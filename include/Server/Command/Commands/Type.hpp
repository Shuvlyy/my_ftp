#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Type final
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
            return "TYPE";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "TYPE <type>";
        }
    };

}
