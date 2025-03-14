/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_get_float
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include <stdlib.h>
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
float print_err(const char *err, const char *path)
{
    fprintf(stderr, "Error: \"%s\": %s\n", path, err);
    return .0f;
}

/**
 * Float getter from node path.
 *
 * @param   yml     YML instance
 * @param   path    Node path
 * @return  Fetched float
 */
float yml_get_float(yml_t *yml, const char *path)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    char *v = NULL;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    v = node->is_list ? node->name : node->value;
    if (v == NULL)
        return print_err(YML_EMPTY_VALUE, path);
    if (!sh_is_str_numeric(v, true, true))
        return print_err(YML_INVALID_TYPE, path);
    return (float) strtod(v, NULL);
}
