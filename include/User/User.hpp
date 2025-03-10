#pragma once

#define USER_ANONYMOUS_NAME     "Anonymous"
#define USER_ANONYMOUS_PASSWORD ""

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
         * @param   defaultCwd  Directory user will be put in at connection
         */
        explicit User(
            std::string username,
            std::string password,
            const std::string &defaultCwd
        );

        /**
         * Creates the default User: Anonymous.
         *
         * @param   defaultCwd  Directory user will be put in at connection
         */
        explicit User(const std::string &defaultCwd);
        ~User() = default;

        [[nodiscard]] std::string getUsername() const;
        [[nodiscard]] std::string getPassword() const;
        [[nodiscard]] std::string getDefaultCwd() const;

    private:
        std::string _username, _password;
        std::string _defaultCwd;
    };

}
