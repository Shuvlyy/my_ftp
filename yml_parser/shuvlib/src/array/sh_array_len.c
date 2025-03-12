/*
** EPITECH PROJECT, 2024
** SH_ARRAY_LEN
** File description:
** Returns the length of an array
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>

size_t sh_array_len(void **array)
{
    int len = 0;

    if (array == NULL)
        return len;
    for (; array[len] != NULL; len++);
    return len;
}
