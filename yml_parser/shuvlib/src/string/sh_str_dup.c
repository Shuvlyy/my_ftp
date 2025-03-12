/*
** EPITECH PROJECT, 2024
** SH_STR_DUP
** File description:
** Duplicates a given string to a new string variable.
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include <stddef.h>
#include "shuvlib/error.h"
#include "shuvlib/string.h"
#include "shuvlib.h"

char *sh_str_dup(char const *src)
{
    char *output = NULL;
    size_t src_len = sh_str_len(src);

    if (src == NULL)
        return NULL;
    output = malloc((src_len + 1) * sizeof(char));
    if (output == NULL)
        return sh_put_nerr(MALLOC_FAIL);
    return sh_str_cpy(output, src);
}
