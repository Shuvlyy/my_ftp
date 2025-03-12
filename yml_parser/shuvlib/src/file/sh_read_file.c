/*
** EPITECH PROJECT, 2024
** SH_READ_FILE
** File description:
** Returns a file's raw content as a string.
** Author: lysandre.boursette@epitech.eu
*/

#include <fcntl.h>
#include <unistd.h>
#include <malloc.h>
#include "shuvlib/file.h"
#include "shuvlib.h"

char *sh_read_file(char *file_path)
{
    int fd;
    size_t file_size = sh_get_file_size(file_path);
    char *buffer;

    if (file_size == 0)
        return NULL;
    fd = open(file_path, O_RDONLY);
    if (fd == FD_FAILURE)
        return NULL;
    buffer = malloc((file_size + 1) * sizeof(char));
    if (buffer == NULL)
        return NULL;
    read(fd, buffer, file_size);
    buffer[file_size] = '\0';
    close(fd);
    return buffer;
}
