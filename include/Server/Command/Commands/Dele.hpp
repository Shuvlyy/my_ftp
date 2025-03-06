#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Dele final
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
            return "DELE";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "This command causes the file specified in the pathname "
                   "to be deleted at the server site.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "DELE <pathname>";
        }
    };

}
