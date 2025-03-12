#include "Server/Command/Commands/Pwd.hpp"
#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include <format>

bool
ftp::server::command::Pwd::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

void
ftp::server::command::Pwd::execute
(
    Server *,
    const std::vector<std::string> &,
    Socket &clientSocket,
    Session &session
)
    const
{
    clientSocket.send(std::format(RES_PWD, session.getWd()));

    /* vv  For more security, but paths needs to be handled that way in other commands too (like RETR, STOR...), and idk if I want to do this.  vv */

    // std::string wd(session.getWd());
    // const std::string defaultCwd(session.getUser()->getDefaultCwd());
    // size_t startingPos = defaultCwd.size();
    //
    // if (defaultCwd == "/") {
    //     startingPos--;
    // }
    // else if (wd == defaultCwd) {
    //     wd += "/";
    // }
    //
    // clientSocket.send(std::format(RES_PWD, wd.substr(startingPos)));
}
