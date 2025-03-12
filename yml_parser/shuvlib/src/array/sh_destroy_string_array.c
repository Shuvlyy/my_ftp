/*
** EPITECH PROJECT, 2024
** SH_DESTROY_STRING_ARRAY
** File description:
** Destroys a string array.
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>

void sh_destroy_string_array(char **array)
{
    if (array == NULL)
        return;
    for (int k = 0; array[k] != NULL; k++)
        free(array[k]);
    free(array);
}
