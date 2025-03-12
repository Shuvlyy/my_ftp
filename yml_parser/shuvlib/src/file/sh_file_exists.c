/*
** EPITECH PROJECT, 2024
** SH_FILE_EXISTS
** File description:
** Returns true if file exists.
** Author: lysandre.boursette@epitech.eu
*/

#include <sys/stat.h>
#include "shuvlib/file.h"

bool sh_file_exists(char const *path)
{
    struct stat stats;

    return stat(path, &stats) != -1;
}
