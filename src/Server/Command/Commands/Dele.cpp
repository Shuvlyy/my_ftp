#include "Server/Command/Commands/Dele.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>

bool
ftp::server::command::Dele::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::Dele::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    const std::string &path = commandArguments.at(0);

    /* FIXME: DUPLICATE FRAGMENT OF CODE (see Session::cwd) -------------------- */
    const std::string absolutePath = Utilities::getAbsolutePath(session.getWd(), path);

    if (!absolutePath.starts_with(session.getUser()->getDefaultWd())) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }
    /* ------------------------------------------------------------------------- */

    if (std::remove(commandArguments.at(0).c_str()) == -1) {
        clientSocket.send(RES_UNKNOWN); // TODO: More precise message pls
        return;
    }

    clientSocket.send(RES_FILE_ACTION_REQ);
}
