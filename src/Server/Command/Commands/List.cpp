#include "Server/Command/Commands/List.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Utilities/Utilities.hpp"

#include "Exception/Exceptions/PathIsNotDir.hpp"
#include "Exception/Exceptions/StandardFunctionFail.hpp"
#include "Exception/Exceptions/WdOutOfScope.hpp"
#include "Exception/Exceptions/FileNotFound.hpp"

#include <filesystem>

bool
ftp::server::command::List::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() <= 1;
}

static void
cleanExit
(
    ftp::server::Session &session
)
{
    session.getDataSocket().closeSocket();
    exit(0);
}

void
ftp::server::command::List::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
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

    const std::string oldPath = session.getWd();

    const std::string &path = commandArguments.size() == 1
        ? commandArguments.at(0)
        : session.getWd();

    /* Entering the folder the user wants to list in */
    try {
        session.cwd(path);
    }
    catch (const exception::PathIsNotDir &) {
        clientSocket.send(RES_NOT_DIR);
        cleanExit(session);
        return;
    }
    catch (const exception::WdOutOfScope &) {
        clientSocket.send(RES_ACTION_NOT_TAKEN);
        cleanExit(session);
        return;
    }
    catch (const exception::FileNotFound &) {
        clientSocket.send(RES_ACTION_NOT_TAKEN); // FIXME: Maybe more precise error message?
        cleanExit(session);
        return;
    }
    catch (const exception::IException &exception) {
        clientSocket.send(RES_UNKNOWN);
        std::cerr << exception;
        cleanExit(session);
        return;
    }

    clientSocket.send(RES_FILE_STATUS_OK);

    try {
        session.getDataSocket().send(Utilities::getDirContents(session.getWd()));
        clientSocket.send(RES_TRANSFER_COMPLETE);
    } catch (const exception::IException &exception) {
        clientSocket.send(RES_TRANSFER_ABORTED);
        std::cerr << exception;
    }

    /* Going back to where the client was */
    session.cwd(oldPath);

    cleanExit(session);
}
