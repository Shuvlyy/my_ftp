#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Pasv final
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
            return "PASV";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "This command requests the server-DTP to \"listen\" "
                   "on a data port (which is not its default data port) and to wait for a "
                   "connection rather than initiate one upon receipt of a "
                   "transfer command. The response to this command includes the "
                   "host and port address this server is listening on.";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "PASV";
        }
    };

}
