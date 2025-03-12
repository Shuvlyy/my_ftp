/*
** EPITECH PROJECT, 2024
** SH_PUT_IERR
** File description:
** Displays an error to the standard error output.
** Returns EXIT_FAILURE
** Author: lysandre.boursette@epitech.eu
*/

#include <unistd.h>
#include "shuvlib/string.h"
#include "shuvlib.h"

int sh_put_ierr(char const *err)
{
    write(STDERR_FILENO, "Error: ", 7);
    write(STDERR_FILENO, err, sh_str_len(err));
    write(STDERR_FILENO, "\n", 1);
    return SH_EXIT_FAILURE;
}
