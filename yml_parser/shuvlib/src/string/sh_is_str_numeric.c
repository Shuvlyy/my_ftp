/*
** EPITECH PROJECT, 2024
** SH_IS_STR_NUMERIC
** File description:
** Returns true if string only contains numbers
** (and minuses/dots if asked so).
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/char.h"
#include "shuvlib/string.h"

bool sh_is_str_numeric(char *str, bool count_minuses, bool count_dots)
{
    for (int k = 0; str[k] != '\0'; k++) {
        if (str[k] == '-' && count_minuses)
            continue;
        if (str[k] == '.' && count_dots)
            continue;
        if (!sh_is_numeric(str[k]))
            return false;
    }
    return true;
}
