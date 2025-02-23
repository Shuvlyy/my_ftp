#pragma once

#include <string>
#include <netinet/in.h>

namespace ftp
{

    class Server final
    {
    public:
        explicit Server(
            short port,
            std::string path
        );
        ~Server();

        void start();
        void stop();

    private:
        int _serverFd;
        sockaddr_in _address;
        socklen_t _addressLen;
        int _port;
        bool _isRunning;
        std::string anonymousUserHomePath;

        void initialize();
        void terminate();
    };

}
