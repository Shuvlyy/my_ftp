#pragma once

#define USER_ANONYMOUS_NAME     "Anonymous"
#define USER_ANONYMOUS_PASSWORD ""
#define USER_UNKNOWN_NAME       "{{$unkn0wn$}}"

#include <string>

namespace ftp
{

    class User final
    {
    public:
        /**
         * Creates a User.
         *
         * @param   username    User name
         * @param   password    Password needed for connection
         * @param   defaultWd   Directory user will be put in at connection
         */
        explicit User(
            std::string username,
            std::string password,
            const std::string &defaultWd
        );

        /**
         * Creates the default User: Anonymous.
         *
         * @param   defaultWd   Directory user will be put in at connection
         */
        explicit User(const std::string &defaultWd);
        ~User() = default;

        [[nodiscard]] std::string getUsername() const;
        [[nodiscard]] std::string getPassword() const;
        [[nodiscard]] std::string getDefaultWd() const;

    private:
        std::string _username, _password;
        std::string _defaultWd;
    };

}
