/*
** EPITECH PROJECT, 2024
** SH_PUT_VERR
** File description:
** Displays an error to the standard error output.
** Returns nothing (void)
** Author: lysandre.boursette@epitech.eu
*/

#include <unistd.h>
#include "shuvlib/string.h"

void sh_put_verr(char const *err)
{
    write(STDERR_FILENO, "Error: ", 7);
    write(STDERR_FILENO, err, sh_str_len(err));
    write(STDERR_FILENO, "\n", 1);
}
