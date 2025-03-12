/*
** EPITECH PROJECT, 2024
** SH_STRSTR
** File description:
** Replicate of the libC "strstr" function.
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/string.h"

char *sh_strstr(char *str, char *delim)
{
    for (; *str != '\0'; str++)
        if (sh_str_ncmp(str, delim, (int) sh_str_len(delim)) == 0)
            return str;
    return NULL;
}
