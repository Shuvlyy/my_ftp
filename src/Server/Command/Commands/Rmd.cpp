#include "Server/Command/Commands/Rmd.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/FileNotFound.hpp"

#include "Utilities/Utilities.hpp"

#include <filesystem>

bool
ftp::server::command::Rmd::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::Rmd::execute
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
    catch (const std::exception &) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    if (!absolutePath.starts_with(session.getUser()->getDefaultWd())) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    if (!fs::is_directory(absolutePath)) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    if (!fs::is_empty(absolutePath)) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: More precise message pls
        return;
    }

    try {
        fs::remove(absolutePath);
        clientSocket.send(RES_FILE_ACTION_REQ);
    } catch (const fs::filesystem_error &) {
        clientSocket.send(RES_UNKNOWN); // TODO: More precise message pls
    }
}
