#include "Server/Signal/Handlers/Int.hpp"
#include "Server/Server.hpp"

void
ftp::server::signal::Int::handle
(
    Server *server
)
    const
{
    server->stop();
}
