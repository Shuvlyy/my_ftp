/*
** EPITECH PROJECT, 2024
** SH_STR_CONTAINS
** File description:
** Returns true if a char is in a string.
** Author: lysandre.boursette@epitech.eu
*/

#include <stdbool.h>

bool sh_str_contains(char const *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] == c)
            return true;
    return false;
}
