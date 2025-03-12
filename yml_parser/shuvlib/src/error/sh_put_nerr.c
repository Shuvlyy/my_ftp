/*
** EPITECH PROJECT, 2024
** SH_PUT_NERR
** File description:
** Displays an error to the standard error output.
** Returns NULL
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include <unistd.h>
#include "shuvlib/string.h"

void *sh_put_nerr(char const *err)
{
    write(STDERR_FILENO, "Error: ", 7);
    write(STDERR_FILENO, err, sh_str_len(err));
    write(STDERR_FILENO, "\n", 1);
    return NULL;
}
