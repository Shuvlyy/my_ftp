/*
** EPITECH PROJECT, 2024
** SH_MEMCPY
** File description:
** Replicate of the "memcpy" function.
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>

char *sh_memcpy(void *dest, const void *src, size_t n)
{
    char *d = (char *) dest;
    char *s = (char *) src;

    for (size_t i = 0; i < n; i++)
        d[i] = s[i];
    return dest;
}
