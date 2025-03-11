#pragma once

#include "Server/Signal/IHandler.hpp"

#include <memory>
#include <unordered_map>

namespace ftp
{
    class Server;
}

namespace ftp::server::sig
{

    class Manager
    {
    public:
        explicit Manager(Server *parent);
        Manager(Manager const &) = delete;
        ~Manager() = default;

    private:
        static Manager *instance;

        Server *_parent;
        std::unordered_map<int, std::unique_ptr<IHandler>> _handlers;

        void registerHandlers();
        void registerHandler(std::unique_ptr<IHandler> handler);
        void setupListener();
        static void dispatchHandler(int signum);
    };

}
