#include "Server/Command/Commands/Dele.hpp"

#include "Exception/Exceptions/WdOutOfScope.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include <filesystem>

bool
ftp::server::commands::Dele::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::commands::Dele::execute
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
    const std::string absolutePath = std::filesystem::weakly_canonical(path);

    if (!absolutePath.starts_with(session.getUser()->getDefaultCwd())) {
        clientSocket.send("out of scope (no permission)!!");
        return;
    }
    /* ------------------------------------------------------------------------- */

    if (std::remove(commandArguments.at(0).c_str()) == -1) {
        clientSocket.send("hmmm probolem");
        return;
    }

    clientSocket.send(RES_FILE_ACTION_REQ);
}
