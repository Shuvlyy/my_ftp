#include "Server/Command/Commands/Stor.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <filesystem>
#include <fstream>

bool
ftp::server::command::Stor::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::command::Stor::startDownload
(
    Session &session,
    const std::string &filepath
)
    const
{
    const Socket &controlSocket = session.getControlSocket();
    const Socket &dataSocket = session.getDataSocket();

    std::ofstream file(filepath, std::ios::binary | std::ios::trunc);

    if (!file.is_open()) {
        session.getControlSocket().send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe a more precise error message.
        return;
    }

    controlSocket.send(RES_FILE_STATUS_OK);

    std::string receivedData;

    while (true) {
        receivedData = dataSocket.receiveBinary();

        if (receivedData.empty()) { // When EOF reached, exit loop.
            break;
        }

        file.write(receivedData.c_str(), static_cast<std::streamsize>(receivedData.size()));
    }

    file.close();

    controlSocket.send(RES_TRANSFER_COMPLETE);
}

void
ftp::server::command::Stor::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    /* FIXME: Code is not really clean... */

    namespace fs = std::filesystem;

    fs::path filepath = weakly_canonical(fs::path(session.getWd()) / fs::path(commandArguments.at(0)));

    if (is_directory(filepath)) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe a more precise error message.
        return;
    }

    if (!filepath.string().starts_with(session.getUser()->getDefaultWd())) {
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

    if (session.getDataSocket().getState() == DataSocket::DEADASS) {
        clientSocket.send(RES_NO_DATA_SOCKET_OPENED);
        exit(0);
    }

    session.getDataSocket().acceptConnection();

    this->startDownload(session, filepath);

    session.getDataSocket().closeSocket();

    exit(0);
}
