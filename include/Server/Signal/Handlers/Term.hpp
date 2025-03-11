#pragma once

#include "Server/Signal/IHandler.hpp"

namespace ftp::server::sig
{

    class Term final
        : public IHandler
    {
    public:
        void handle(Server *server) const override;

        [[nodiscard]] int getSignalNumber()
            const override
        {
            return SIGTERM;
        };
    };

}
