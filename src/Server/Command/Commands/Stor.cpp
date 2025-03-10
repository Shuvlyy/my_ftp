#include "Server/Command/Commands/Stor.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <filesystem>

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
ftp::server::command::Stor::execute
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

    const int pid = fourchette();

    if (pid < 0) {
        throw exception::StandardFunctionFail("fork");
    }

    if (pid > 0) { // In parent, skip.
        return;
    }

//    const std::string oldPath = session.getWd();
//
//    const std::string &path = commandArguments.size() == 1
//        ? commandArguments.at(0)
//        : session.getWd();
//
//    /* Entering the folder the user wants to list in */
//    try {
//        session.cwd(path);
//    }
//    catch (const exception::PathIsNotDir &) {
//        clientSocket.send(RES_NOT_DIR);
//        return;
//    }
//    catch (const exception::WdOutOfScope &) {
//        clientSocket.send(RES_ACTION_NOT_TAKEN);
//        return;
//    }
//    catch (const exception::IException &exception) {
//        clientSocket.send(RES_UNKNOWN);
//        std::cerr << exception;
//        return;
//    }
//
//    clientSocket.send(RES_FILE_STATUS_OK);
//
//    try {
//        session.getDataSocket().send(Utilities::getDirContents(session.getWd()));
//        clientSocket.send(RES_TRANSFER_COMPLETE);
//    } catch (const exception::IException &exception) {
//        clientSocket.send(RES_TRANSFER_ABORTED);
//        std::cerr << exception;
//    }
//
//    /* Going back to where the client was */
//    session.cwd(oldPath);

    session.getDataSocket().closeSocket();

    exit(0);
}
