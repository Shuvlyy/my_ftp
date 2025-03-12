/*
** EPITECH PROJECT, 2023
** SH_STR_LEN
** File description:
** Returns the length of a given string.
** Replicate of the libC "strlen" function.
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>

size_t sh_str_len(char const *str)
{
    int length = 0;

    if (str == NULL)
        return length;
    for (; str[length] != '\0'; length++);
    return length;
}
