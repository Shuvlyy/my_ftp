#include "Server/Command/Commands/Port.hpp"

#include "Server/Server.hpp"

#include "Common/Responses.hpp"

#include "Exception/Exceptions/InvalidCommandUsage.hpp"
#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <format>
#include <sstream>

bool
ftp::server::commands::Port::isUsageValid
(
    const std::vector<std::string> &commandArguments
)
    const
{
    if (commandArguments.size() != 1) {
        return false;
    }

    size_t commaAmount = 0;

    for (const auto &c : commandArguments.at(0)) {
        if (c == ',') {
            commaAmount++;
        }
    }

    return commaAmount == 5;
}

std::vector<int>
ftp::server::commands::Port::parseArgs
(
    const std::string &arg
)
    const
{
    std::vector<int> tokens;
    std::istringstream stream(arg);
    std::string currentToken;

    while (std::getline(stream, currentToken, ',')) {
        int token = std::stoi(currentToken); // FIXME: Hmmm, maybe use a more secure function to convert the string into an integer (c.f. std::strtol).

        if (token == -1) {
            throw exception::InvalidCommandUsage(this);
        }

        tokens.push_back(token);
    }
    return tokens;
}

void
ftp::server::commands::Port::execute
(
    Server *,
    const std::vector<std::string> &commandArguments,
    Socket &clientSocket,
    Session &session
)
    const
{
    const std::vector<int> tokens = this->parseArgs(commandArguments.at(0));

    DataSocket &dataSocket = session.getDataSocket();

    dataSocket.closeSocket();

    std::stringstream ip;
    ip << tokens.at(0) << '.' << tokens.at(1) << '.' << tokens.at(2) << '.' << tokens.at(3);

    try {
        dataSocket = DataSocket(
            ip.str(),
            static_cast<unsigned short>(tokens.at(4) * 256 + tokens.at(5))
        );
    }
    catch (const exception::IException &exception) {
        clientSocket.send(RES_CANT_OPEN_DATA);
        std::cerr << exception;
        return;
    }

    clientSocket.send(std::format(RES_COMMAND_OK, this->getCommandName()));
}
