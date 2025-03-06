#include "Parser/Parser.hpp"

#include <filesystem>

#include "Exception/Exceptions/InvalidUsage.hpp"
#include "Exception/Exceptions/UnknownFlag.hpp"
#include "Exception/Exceptions/PathIsNotDir.hpp"

#include "Utilities/Utilities.hpp"

#include <iostream>

ftp::Parser::Parser
(
    const int argc,
    char *argv[]
)
    : _port()
{
    this->parse(argc, argv);
}

void
ftp::Parser::parse
(
    const int argc,
    char *argv[]
)
{
    for (int k = 1; k < argc; ++k) {
        this->_tokens.emplace_back(argv[k]);
    }

    if (this->_tokens.empty()) {
        throw exception::InvalidUsage();
    }

    if (this->_tokens.at(0)[0] != '-') {
        if (this->_tokens.size() != 2) {
            throw exception::InvalidUsage();
        }

        this->_port = static_cast<unsigned short>(Utilities::stringToInt(this->_tokens.at(0)));
        this->_path = this->_tokens.at(1);

        if (!(std::filesystem::is_directory(this->_path) &&
            std::filesystem::exists(this->_path))) {
            throw exception::PathIsNotDir(this->_path);
        }
    }
}

bool
ftp::Parser::processFlags
()
    const
{
    if (!this->_tokens.empty() && this->_tokens.at(0)[0] != '-') {
        return false;
    }

    if (this->hasFlag("-help")) {
        std::cout << "USAGE: ./myftp port path" << std::endl
                  << "\tport is the port number on which the server socket listens" << std::endl
                  << "\tpath is the path to the home directory for the Anonymous user" << std::endl;
        return true;
    }

    if (this->hasFlag("-about")) {
        std::cout << "NWP-400: my_ftp" << std::endl
                  << "Written by Lysandre BOURSETTE (@shuvlyy)" << std::endl;
        return true;
    }

    throw exception::UnknownFlag(this->_tokens.at(0));
}

unsigned short
ftp::Parser::getPort
()
    const
{
    return this->_port;
}

std::string
ftp::Parser::getPath
()
    const
{
    return this->_path;
}

bool
ftp::Parser::hasFlag
(
    const std::string &flag
)
    const
{
    for (auto &token : this->_tokens) {
        if (token == flag) {
            return true;
        }
    }
    return false;
}

std::string
ftp::Parser::getFlagValue
(
    const std::string &flag
)
    const
{
    for (size_t k = 0; k < this->_tokens.size(); ++k) {
        if (this->_tokens.at(k) == flag &&
            this->_tokens.size() >= k + 1) {
            return this->_tokens.at(k + 1);
        }
    }
    return {}; // Null string
}
