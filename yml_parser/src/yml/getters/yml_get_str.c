/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_get_str
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include "yml.h"

/**
 * Prints out an error.
 *
 * @param   err     Error
 * @param   path    Node path
 * @return  Default value (0)
 */
static
char *print_err(const char *err, const char *path)
{
    printf("Error: \"%s\": %s\n", path, err);
    return NULL;
}

/**
 * String getter from node path.
 *
 * @param   yml     YML instance
 * @param   path    Node path
 * @return  Fetched string
 */
char *yml_get_str(yml_t *yml, const char *path)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    char *v = NULL;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    v = node->is_list ? node->name : node->value;
    if (v == NULL)
        return print_err(YML_EMPTY_VALUE, path);
    return v;
}
