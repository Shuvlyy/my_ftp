#pragma once

#include "ICommand.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ftp
{
    class Server;
}

namespace ftp::server::command
{

    class Manager
    {
    public:
        explicit Manager(Server *parent);
        Manager(Manager const &) = delete;
        ~Manager() = default;

        std::vector<ICommand *> getCommands() const;
        ICommand *getCommand(const std::string &commandName) const;

        void executeCommand(
            const std::string &commandName,
            std::vector<std::string> &commandArguments,
            Socket &clientSocket
        ) const;

        void executeCommand(
            const std::string &commandName,
            Socket &clientSocket
        ) const;

    private:
        Server *_parent;
        std::unordered_map<std::string, std::unique_ptr<ICommand>> _commands;

        void registerCommands();
        void registerCommand(std::unique_ptr<ICommand> command);
    };

}
