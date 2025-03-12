/*
** EPITECH PROJECT, 2024
** SH_MULTITOK
** File description:
** strtok but with a full string delimiter
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include "shuvlib/string.h"

char *sh_multitok(char *input, char *delimiter)
{
    static char *string;
    char *end = NULL;
    char *tmp = NULL;

    if (input != NULL)
        string = input;
    if (string == NULL)
        return string;
    end = sh_strstr(string, delimiter);
    if (end == NULL) {
        tmp = string;
        string = NULL;
        return tmp;
    }
    tmp = string;
    *end = '\0';
    string = end + sh_str_len(delimiter);
    return tmp;
}
