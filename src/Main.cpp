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
    // const ftp::logger::Log log(
    //     ftp::logger::Log::Level::COMMAND,
    //     "192.168.1.40",
    //     "admin",
    //     "PASS admin",
    //     "200 PASS okay."
    // );

    try {
        const ftp::Parser parser(argc, argv);

        if (parser.processFlags()) {
            return SH_EXIT_SUCCESS;
        }

        const std::string configFile = parser.getFlagValue("--config");

        ftp::Server server(parser.getPort(), parser.getPath(), configFile);
        // ftp::Dashboard dashboard(&server);

        // dashboard.initialize();

        // server.setDashboardInstance(&dashboard);

        // server.getLogger().log(log);

        server.start();
    }
    catch (ftp::exception::IException &exception) {
        std::cerr << exception;
        return SH_EXIT_FAILURE;
    }

    return SH_EXIT_SUCCESS;
}
