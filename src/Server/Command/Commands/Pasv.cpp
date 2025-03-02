#include "Server/Command/Commands/Pasv.hpp"

#include "Common/Responses.hpp"

#include "Server/Server.hpp"

#include <format>
#include <sstream>
#include <arpa/inet.h>

bool
ftp::server::commands::Pasv::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    return commandArguments.empty();
}

static std::vector<int>
parseIp
(
    const std::string &ip
)
{
    std::vector<int> tokens;
    std::istringstream stream(ip);
    std::string currentToken;

    while (std::getline(stream, currentToken, '.')) {
        tokens.push_back(std::stoi(currentToken)); // FIXME: A bit ugly.
    }
    return tokens;
}

void
ftp::server::commands::Pasv::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    DataSocket &dataSocket = session.getDataSocket();

    dataSocket.closeSocket();
    dataSocket = DataSocket();

    const char *serverIp = inet_ntoa(dataSocket.getAddress().sin_addr);
    const uint16_t port = ntohs(dataSocket.getAddress().sin_port);
    std::vector<int> ipTokens = parseIp(serverIp);

    // "227 Entering Passive Mode ({},{},{},{},{},{})."
    clientSocket.send(std::format(
        RES_ENTERING_PASSIVE_MODE,
        ipTokens.at(0), ipTokens.at(1), ipTokens.at(2), ipTokens.at(3),
        port / 256, port % 256
    ));
}
