#pragma once

#define PROTOCOL_ANY    0
#define BUFFER_SIZE     1024

#include <string>

namespace ftp::server
{

    class Socket final
    {
    public:
        explicit Socket(short port);
        ~Socket();

        void send(const std::string &data) const;
        [[nodiscard]] std::string receive() const;

        [[nodiscard]] int getFd() const;

    private:
        int _fd;

        void initialize(short port);
        void _close();
    };

}
