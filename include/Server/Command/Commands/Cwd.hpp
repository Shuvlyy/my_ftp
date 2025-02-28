#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Cwd final
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
            return "CWD";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "CHANGE WORKING DIRECTOR: This command allows the user "
                    "to work with a different directory or dataset for file storage "
                    "or retrieval without altering his login or accounting information.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "CWD <pathname>";
        }
    };

}
