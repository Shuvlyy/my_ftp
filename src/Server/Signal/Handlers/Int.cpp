#include "Server/Signal/Handlers/Int.hpp"
#include "Server/Server.hpp"

void
ftp::server::sig::Int::handle
(
    Server *server
)
    const
{
    server->stop();
}
