#include "Server/Server.hpp"

#include "Exception/AException.hpp"

#include "Parser/Parser.hpp"

#define SH_EXIT_SUCCESS 0
#define SH_EXIT_FAILURE 84

int
main
(
    const int argc,
    char *argv[]
)
{
    try {
        const ftp::Parser parser(argc, argv);

        if (parser.processFlags()) {
            return SH_EXIT_SUCCESS;
        }

        ftp::Server server(parser.getPort(), parser.getPath());

        server.start();
    }
    catch (ftp::exception::IException &exception) {
        std::cerr << exception;
        return SH_EXIT_FAILURE;
    }

    return SH_EXIT_SUCCESS;
}
