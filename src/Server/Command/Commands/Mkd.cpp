#include "Server/Command/Commands/Mkd.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/IException.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>
#include <format>

bool
ftp::server::command::Mkd::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::Mkd::execute
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

    std::string absolutePath;

    try {
        absolutePath = Utilities::getAbsolutePath(session.getWd(), path);
    }
    catch (const exception::IException &) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    if (!absolutePath.starts_with(session.getUser()->getDefaultWd())) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    if (fs::exists(absolutePath)) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    try {
        if (fs::create_directory(absolutePath)) {
            clientSocket.send(std::format(RES_PATH_CREATED, path));
        } else {
            clientSocket.send(RES_UNKNOWN);
        }
    } catch (const std::filesystem::filesystem_error &) {
        clientSocket.send(RES_UNKNOWN);
    }
}
