/*
** EPITECH PROJECT, 2024
** SH_PUT_STR
** File description:
** Puts a string to the standard output.
** Author: lysandre.boursette@epitech.eu
*/

#include <unistd.h>
#include "shuvlib/string.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

ssize_t sh_put_str(char const *str)
{
    ssize_t result = write(STDOUT_FILENO, str, sh_str_len(str));

    if (result == -1)
        return sh_put_ierr(WRITE_FAIL);
    return result;
}
