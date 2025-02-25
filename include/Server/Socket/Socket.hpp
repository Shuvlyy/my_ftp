#pragma once

#define PROTOCOL_ANY 0

namespace ftp::server
{

    class Socket final
    {
    public:
        explicit Socket(short port);

        [[nodiscard]] int getFd() const;

    private:
        int _fd;

        void initialize(short port);
    };

}
