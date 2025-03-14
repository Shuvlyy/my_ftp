/*
** EPITECH PROJECT, 2025
** yml_parser
** File description:
** yml_get_bool
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include "yml.h"
#include "shuvlib/string.h"

/**
 * Prints out an error.
 *
 * @param   err     Error
 * @param   path    Node path
 * @return  Default value (0)
 */
static
bool print_err(const char *err, const char *path)
{
    fprintf(stderr, "Error: \"%s\": %s\n", path, err);
    return false;
}

/**
 * String getter from node path.
 *
 * @param   yml     YML instance
 * @param   path    Node path
 * @return  Fetched boolean
 */
bool yml_get_bool(yml_t *yml, const char *path)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    char *v = NULL;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    v = node->is_list ? node->name : node->value;
    if (v == NULL)
        return print_err(YML_EMPTY_VALUE, path);
    if (sh_str_cmp(v, "true") == 0)
        return true;
    if (sh_str_cmp(v, "false") == 0)
        return false;
    return print_err(YML_INVALID_TYPE, path);
}
