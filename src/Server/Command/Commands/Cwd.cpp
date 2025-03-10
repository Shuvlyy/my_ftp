#include "Server/Command/Commands/Cwd.hpp"

#include "Exception/Exceptions/PathIsNotDir.hpp"
#include "Exception/Exceptions/WdOutOfScope.hpp"
#include "Exception/Exceptions/FileNotFound.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

bool
ftp::server::commands::Cwd::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.size() == 1;
}

void
ftp::server::commands::Cwd::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    try {
        session.cwd(commandArguments.at(0));
        clientSocket.send(RES_FILE_ACTION_REQ);
    }
    catch (exception::FileNotFound &exception) {
        std::cerr << exception;
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: Maybe a more specific error code?
    }
    catch (exception::PathIsNotDir &exception) {
        std::cerr << exception;
        clientSocket.send(RES_ACTION_NOT_TAKEN); // TODO: Maybe a more specific error code?
    }
    catch (exception::WdOutOfScope &exception) {
        std::cerr << exception;
        clientSocket.send(RES_ACTION_NOT_TAKEN);
    }
    catch (exception::IException &exception) {
        std::cerr << exception;
        clientSocket.send(RES_UNKNOWN);
    }
}
