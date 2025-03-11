#include "Server/Signal/Handlers/Term.hpp"
#include "Server/Server.hpp"

void
ftp::server::sig::Term::handle
(
    Server *server
)
    const
{
    server->stop();
}
