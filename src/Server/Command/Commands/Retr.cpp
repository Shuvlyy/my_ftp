#include "Server/Command/Commands/Retr.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"
#include "Exception/Exceptions/FileNotFound.hpp"

#include <filesystem>
#include <fstream>
#include "Utilities/Utilities.hpp"

bool
ftp::server::command::Retr::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::Retr::startUpload
(
    Session &session,
    const std::string &filepath
)
    const
{
    const Socket &controlSocket = session.getControlSocket();
    const Socket &dataSocket = session.getDataSocket();

    std::ifstream file(filepath, std::ios::binary);

    if (!file.is_open()) {
        controlSocket.send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe a more precise way?
        return;
    }

    controlSocket.send(RES_FILE_STATUS_OK);

    char buffer[BUFFER_SIZE];

    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        dataSocket.send(std::string(buffer, file.gcount()));
    }

    file.close();

    controlSocket.send(RES_TRANSFER_COMPLETE);
}

void
ftp::server::command::Retr::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    if (session.getDataSocket().getFd() == -1) {
        clientSocket.send(RES_NO_DATA_SOCKET_OPENED);
        return;
    }

    std::string filepath;

    try {
        filepath = Utilities::getAbsolutePath(session.getWd(), commandArguments.at(0));
    }
    catch (const exception::FileNotFound &) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe a more precise error message.
        return;
    }

    if (!filepath.starts_with(session.getUser()->getDefaultCwd())) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe a more precise error message.
        return;
    }

    if (std::filesystem::is_directory(filepath)) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe a more precise error message.
        return;
    }

    const int pid = fourchette();

    if (pid < 0) {
        throw exception::StandardFunctionFail("fork");
    }

    if (pid > 0) { // In parent, skip.
        return;
    }

    this->startUpload(session, filepath);

    session.getDataSocket().closeSocket();

    exit(0);
}
