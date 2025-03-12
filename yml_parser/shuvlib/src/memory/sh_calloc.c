/*
** EPITECH PROJECT, 2024
** SH_CALLOC
** File description:
** Replicate of the libC "calloc" system function.
** Basically a malloc with memset.
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include "shuvlib/memory.h"

void *sh_calloc(size_t size, int value)
{
    void *output = malloc(size);

    if (output == NULL)
        return NULL;
    sh_memset(output, value, size);
    return output;
}
