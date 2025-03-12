/// Not the best filename.

#include "Utilities/Utilities.hpp"

#include "Exception/Exceptions/StandardFunctionFail.hpp"

#include <filesystem>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>

static char
parseMode
(
    const mode_t mode
)
{
    const std::string format("lcdbps-");
    const int masks[7] = {
        S_IFLNK, S_IFCHR, S_IFDIR, S_IFBLK, S_IFIFO, S_IFSOCK, S_IFREG
    };

    for (int k = 0; format[k] != '\0'; k++) {
        if (__S_ISTYPE(mode, masks[k])) {
            return format[k];
        }
    }
    return '-'; // TODO: Maybe return '?' instead?
}

static std::string
parseFilePermissions
(
    const __mode_t mode
)
{
    const char rwx[4] = "rwx";
    char perms[10] = "---------";
    const int masks[9] = {
        S_IRUSR, S_IWUSR, S_IXUSR,
        S_IRGRP, S_IWGRP, S_IXGRP,
        S_IROTH, S_IWOTH, S_IXOTH
    };

    for (int k = 0; perms[k] != '\0'; k++) {
        if (mode & masks[k]) {
            perms[k] = rwx[k % 3];
        }
    }
    if (mode & S_ISVTX) {
        perms[8] = 'T';
    }
    return perms;
}

static std::string
getUsernameFromUid
(
    const uid_t uid
)
{
    const passwd *pwd = getpwuid(uid);

    if (pwd == nullptr) {
        return "?";
    }
    return pwd->pw_name;
}

static std::string
getUsernameFromGid
(
    const gid_t gid
)
{
    const group *grp = getgrgid(gid);

    if (grp == nullptr) {
        return "?";
    }
    return grp->gr_name;
}

static std::string
getFileDate(const struct stat *fileStat)
{
    return std::string(ctime(&fileStat->st_mtim.tv_sec))
        .substr(4, 6);
}

static std::string
getFileTime(const struct stat *fileStat)
{
    const time_t nowSec = time(nullptr);
    const ssize_t fileCreationSec = fileStat->st_mtim.tv_sec;
    const std::string formattedDate = ctime(&fileStat->st_mtim.tv_sec);

    if (nowSec < fileCreationSec + SIX_MONTHS_SEC) {
        return formattedDate.substr(11, 5);
    }
    return formattedDate.substr(20, 4);
}

std::string
ftp::Utilities::getDirContents
(
    const std::string &filepath
)
{
    std::ostringstream output;

    for (const auto &entry : std::filesystem::directory_iterator(filepath)) {
        struct stat entryStat {};

        if (stat(entry.path().c_str(), &entryStat) < 0) {
            throw exception::StandardFunctionFail("stat");
        }

        const char mode = parseMode(entryStat.st_mode);
        const std::string permissions = parseFilePermissions(entryStat.st_mode);
        const size_t links = entryStat.st_nlink;
        const std::string uidUsername = getUsernameFromUid(entryStat.st_uid);
        const std::string gidUsername = getUsernameFromGid(entryStat.st_gid);
        const int minor = minor(entryStat.st_dev);
        const int major = major(entryStat.st_dev);
        const ssize_t size = entryStat.st_size;
        const std::string date = getFileDate(&entryStat);
        const std::string time = getFileTime(&entryStat);
        std::string filename(entry.path().filename());

        output << mode << permissions << " " << links << " " << uidUsername << " " << gidUsername << " ";
        if (S_ISCHR(entryStat.st_mode)) {
            output << minor << ", " << major;
        } else {
            output << size;
        }

        output << " " << date << " " << time << " " << filename << std::endl;
    }

    std::string res(output.str());

    res.pop_back();

    return res;
}
