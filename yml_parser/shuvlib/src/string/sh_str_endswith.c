/*
** EPITECH PROJECT, 2024
** SH_STR_ENDSWITH
** File description:
** Returns true if given string ends with other given string.
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/string.h"

bool sh_str_endswith(char *str, char *ends_with)
{
    size_t str_len = sh_str_len(str);
    size_t ends_with_len = sh_str_len(ends_with);

    return sh_str_cmp(str + str_len - ends_with_len, ends_with) == 0;
}
