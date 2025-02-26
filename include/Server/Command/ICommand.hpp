#pragma once

#include "Server/Socket/Socket.hpp"

#include <string>
#include <vector>

namespace ftp
{
    class Server;
}

namespace ftp::server::commands
{

    class ICommand
    {
    public:
        ICommand() = default;
        virtual ~ICommand() = default;

        [[nodiscard]] virtual bool isUsageValid(
            const std::vector<std::string> &commandArguments
        ) const = 0;

        virtual void execute(
            Server *server,
            const std::vector<std::string> &commandArguments,
            const Socket &clientSocket
        ) const = 0;

        [[nodiscard]] virtual std::string getCommandName() const = 0;
        [[nodiscard]] virtual std::string getCommandDescription() const = 0;
        [[nodiscard]] virtual std::string getCommandSyntax() const = 0;
    };

}
