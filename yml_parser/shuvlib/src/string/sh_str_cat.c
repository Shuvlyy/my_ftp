/*
** EPITECH PROJECT, 2024
** SH_STR_CAT
** File description:
** Concats a given string to another string and then returns it.
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include <string.h>
#include "shuvlib/string.h"
#include "shuvlib/memory.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

char *sh_str_cat(char *dest, char const *src)
{
    size_t dest_len = 0;
    size_t src_len = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    dest_len = sh_str_len(dest);
    src_len = sh_str_len(src);
    dest = sh_realloc(dest, (dest_len + src_len + 1) * sizeof(char));
    if (dest == NULL)
        return sh_put_nerr(MALLOC_FAIL);
    dest[dest_len + src_len] = '\0';
    return sh_str_cpy(dest + dest_len, src);
}
