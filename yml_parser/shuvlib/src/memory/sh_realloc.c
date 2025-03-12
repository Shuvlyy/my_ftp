/*
** EPITECH PROJECT, 2024
** SH_REALLOC
** File description:
** Replicate of the "realloc" function.
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include <string.h>
#include "shuvlib/error.h"
#include "shuvlib/memory.h"
#include "shuvlib/string.h"
#include "shuvlib.h"

void *sh_realloc(void *ptr, size_t size)
{
    void *new_ptr = NULL;

    if (ptr == NULL)
        return sh_calloc(size, 0);
    if (size == 0)
        return free(ptr), NULL;
    new_ptr = sh_calloc(size, 0);
    if (new_ptr == NULL)
        return free(ptr), sh_put_nerr(MALLOC_FAIL);
    memcpy(new_ptr, ptr, size);
    return new_ptr;
}
