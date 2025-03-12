/*
** EPITECH PROJECT, 2024
** SH_GET_FILE_SIZE
** File description:
** Returns the size of a file
** Author: lysandre.boursette@epitech.eu
*/

#include <sys/stat.h>
#include "shuvlib/file.h"
#include "shuvlib.h"

size_t sh_get_file_size(char *file_path)
{
    struct stat file_stats;

    if (stat(file_path, &file_stats) == FD_FAILURE)
        return 0;
    return file_stats.st_size;
}
