/*
** EPITECH PROJECT, 2024
** FILE_H_
** File description:
** File library header
** Author: lysandre.boursette@epitech.eu
*/

#ifndef FILE_H_
    #define FILE_H_

    #include <stddef.h>
    #include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    char *sh_read_file(char *file_path);
    size_t sh_get_file_size(char *file_path);
    bool sh_file_exists(char const *path);

#ifdef __cplusplus
}
#endif

#endif
