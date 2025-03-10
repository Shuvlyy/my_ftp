#pragma once

#include "ICommand.hpp"

namespace ftp::server::command
{

    class ACommand
        : public ICommand
    {
    public:
        [[nodiscard]] bool
        doesNeedLogin()
            const override
        {
            return true;
        }
    };

}
