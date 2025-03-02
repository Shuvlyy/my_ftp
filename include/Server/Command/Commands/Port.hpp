#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::commands
{

    class Port final
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
            return "PORT";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "The argument is a HOST-PORT specification for the "
                   "data port to be used in data connection. A port command would be: "
                   "PORT h1,h2,h3,h4,p1,p2";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "PORT <host-port>";
        }

    private:
        [[nodiscard]] std::vector<int> parseArgs(const std::string &arg) const;
    };

}
