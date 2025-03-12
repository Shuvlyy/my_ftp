/*
** EPITECH PROJECT, 2024
** SH_REMOVE_TRAILING_SPACES
** File description:
** Removes the trailing spaces from a given string.
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include "shuvlib/string.h"

void sh_remove_trailing_spaces(char *str)
{
    int start = 0;
    int end = sh_str_len(str) - 1;
    int i = 0;

    if (str == NULL)
        return;
    while (str[start] == ' ' || str[start] == '\t')
        start++;
    while (end > start && (str[end] == ' ' || str[end] == '\t'))
        end--;
    while (start <= end) {
        str[i] = str[start];
        i++;
        start++;
    }
    str[i] = '\0';
}
