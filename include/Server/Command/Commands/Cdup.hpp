#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::command
{

    class Cdup final
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
            return "CDUP";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "CHANGE TO PARENT DIRECTORY: "
                    "This command is a special case of CWD";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "CDUP";
        }
    };

}
