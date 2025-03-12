/*
** EPITECH PROJECT, 2024
** SH_PUT_IERR
** File description:
** Displays an error to the standard error output.
** Returns false
** Author: lysandre.boursette@epitech.eu
*/

#include <unistd.h>
#include "shuvlib/error.h"
#include "shuvlib/string.h"

bool sh_put_berr(char const *err)
{
    write(STDERR_FILENO, "Error: ", 7);
    write(STDERR_FILENO, err, sh_str_len(err));
    write(STDERR_FILENO, "\n", 1);
    return false;
}
