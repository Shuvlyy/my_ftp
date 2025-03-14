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
    namespace fs = std::filesystem;

    const std::string &path = commandArguments.at(0);

    const std::string absolutePath = Utilities::getAbsolutePath(session.getWd(), path);

    if (!absolutePath.starts_with(session.getUser()->getDefaultWd())) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    if (!fs::exists(absolutePath) || fs::is_directory(absolutePath)) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    try {
        fs::remove(commandArguments.at(0));
        clientSocket.send(RES_FILE_ACTION_REQ);
    }
    catch (const std::filesystem::filesystem_error &exception) {
        clientSocket.send(RES_UNKNOWN);
        std::cerr << exception.what() << std::endl;
    }
}
