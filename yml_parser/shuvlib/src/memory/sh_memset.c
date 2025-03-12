/*
** EPITECH PROJECT, 2024
** SH_MEMSET
** File description:
** Replicate of the libC "memset" system function.
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/memory.h"

void *sh_memset(void *ptr, int value, size_t n)
{
    unsigned char *p = ptr;

    for (; n--; p++)
        *p = value;
    return ptr;
}
