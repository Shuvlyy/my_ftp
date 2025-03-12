#pragma once

#include <string>

namespace ftp::logger
{

    class Log final
    {
    public:
        enum Level
        {
            DEBUG,
            INFO,
            COMMAND,
            WARN,
            ERROR,
            CRITICAL,
            FATAL
        };

        explicit Log(
            Level level,
            std::string authorIp,
            std::string authorUser,
            std::string body,
            std::string response
        );

        [[nodiscard]] std::string compute() const;

    private:
        Level _level;
        time_t _creationTime;
        std::string _authorIp;
        std::string _authorUser;
        std::string _body;
        std::string _response;

        [[nodiscard]] std::string formatCreationTime() const;
    };

}
