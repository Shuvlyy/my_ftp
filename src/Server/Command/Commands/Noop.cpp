#include "Server/Command/Commands/Noop.hpp"

bool
ftp::server::commands::Noop::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::commands::Noop::execute
(
    Server *,
    const std::vector<std::string> &,
    Socket &,
    Session &
)
    const
{
    // LALALALALLALALALALALALALALLALA
}
