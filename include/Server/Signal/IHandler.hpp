// ReSharper disable CppUnusedIncludeDirective
#pragma once

#include <iostream>
#include <csignal>

namespace ftp
{
    class Server;
}

namespace ftp::server::signal
{

    class IHandler
    {
    public:
        IHandler() = default;
        virtual ~IHandler() = default;

        virtual void handle(Server *server) const = 0;

        [[nodiscard]] virtual int getSignalNumber() const = 0;
    };

}
