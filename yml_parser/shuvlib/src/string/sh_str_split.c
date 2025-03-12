/*
** EPITECH PROJECT, 2023
** SH_STR_SPLIT
** File description:
** Splits a string into an array of strings
** based on the given delimiter.
** Inspired from the python "split" function.
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "shuvlib/string.h"

static
int count_args(char *str, char const *delims)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++)
        count += sh_str_contains(delims, str[i]);
    return count;
}

char **sh_str_split(char *str, char *delims, bool multi)
{
    char *s = sh_str_dup(str);
    char **output = malloc((count_args(str, delims) + 2) * sizeof(char *));
    int i = 0;
    char *curr_token = multi ? sh_multitok(s, delims) : strtok(s, delims);

    if (output == NULL)
        return free(s), NULL;
    if (str == NULL || str[0] == '\0' || curr_token == NULL) {
        free(s);
        return free(output), NULL;
    }
    for (; curr_token != NULL; i++) {
        output[i] = sh_str_dup(curr_token);
        curr_token = multi ? sh_multitok(NULL, delims) : strtok(NULL, delims);
    }
    output[i] = NULL;
    free(s);
    return output;
}
