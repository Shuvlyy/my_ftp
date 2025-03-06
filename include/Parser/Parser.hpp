#pragma once

#include <string>
#include <vector>

namespace ftp
{

    class Parser final
    {
    public:
        Parser(
            int argc,
            char *argv[]
        );

        /**
         * @returns  true if program should terminate after processing flags. Otherwise, false.
         */
        [[nodiscard]] bool processFlags() const;

        [[nodiscard]] unsigned short getPort() const;
        [[nodiscard]] std::string getPath() const;
        [[nodiscard]] bool hasFlag(const std::string &flag) const;
        [[nodiscard]] std::string getFlagValue(const std::string &flag) const;

    private:
        unsigned short _port;
        std::string _path;
        std::vector<std::string> _tokens;

        void parse(int argc, char *argv[]);
    };

}
