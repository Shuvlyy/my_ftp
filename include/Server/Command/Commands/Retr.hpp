#pragma once

#include "Server/Command/ACommand.hpp"

namespace ftp::server::command
{

    class Retr final
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
            return "RETR";
        }

        [[nodiscard]] std::string getCommandDescription()
            const override
        {
            return "";
        }

        [[nodiscard]] std::string getCommandSyntax()
            const override
        {
            return "RETR <pathname>";
        }

    private:
        void startDownload(Session &session, const std::string &filepath) const;
    };

}
