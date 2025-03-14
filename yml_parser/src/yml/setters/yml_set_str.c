/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_set_str
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include <malloc.h>
#include "yml.h"
#include "shuvlib/string.h"
#include "shuvlib.h"

/**
 * Prints out an error.
 *
 * @param   err     Error
 * @param   path    Node path
 * @return  Default value (SH_EXIT_FAILURE)
 */
static
int print_err(const char *err, const char *path)
{
    fprintf(stderr, "Error: \"%s\": %s\n", path, err);
    return SH_EXIT_FAILURE;
}

/**
 * Updates targeted field with a given value.
 *
 * @param   dest    Targeted field
 * @param   value   Value
 * @return  Default value (SH_EXIT_SUCCESS)
 */
static
int set_value(char **dest, const char *value)
{
    free(*dest);
    *dest = sh_str_dup(value);
    return SH_EXIT_SUCCESS;
}

/**
 * Float setter from node path.
 *
 * @param   yml     YML instance
 * @param   path    Node path
 * @param   value   Value to set
 * @return  SH_EXIT_SUCCESS on success, otherwise SH_EXIT_FAILURE
 */
int yml_set_str(yml_t *yml, const char *path, const char *value)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    char **v = NULL;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    v = node->is_list ? &node->name : &node->value;
    if (v == NULL)
        return print_err(YML_EMPTY_VALUE, path);
    return set_value(v, value);
}
