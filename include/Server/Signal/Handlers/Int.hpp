#pragma once

#include "Server/Signal/IHandler.hpp"

namespace ftp::server::signal
{

    class Int final
        : public IHandler
    {
    public:
        void handle(Server *server) const override;

        [[nodiscard]] int getSignalNumber()
            const override
        {
            return SIGINT;
        };
    };

}
