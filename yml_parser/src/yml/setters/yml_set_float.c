/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_set_float
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include <malloc.h>
#include "yml.h"
#include "shuvlib/string.h"
#include "shuvlib/error.h"
#include "shuvlib/memory.h"
#include "shuvlib.h"

/**
 * Prints out an error.
 *
 * @param   err     Error
 * @param   path    Node path
 * @return  Default value (SH_EXIT_FAILURE)
 */
static
int print_err(char *err, char *path)
{
    printf("Error: \"%s\": %s\n", path, err);
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
int set_value(char **dest, float value)
{
    int length = snprintf(NULL, 0, "%f", value);

    free(*dest);
    *dest = sh_calloc((length + 1) * sizeof(char), 0);
    if (*dest == NULL)
        return sh_put_ierr(MALLOC_FAIL);
    snprintf(*dest, length + 1, "%f", value);
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
int yml_set_float(yml_t *yml, char *path, float value)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    char **v = NULL;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    v = node->is_list ? &node->name : &node->value;
    if (v == NULL)
        return print_err(YML_EMPTY_VALUE, path);
    if (!sh_is_str_numeric(*v, true, true))
        return print_err(YML_INVALID_TYPE, path);
    return set_value(v, value);
}
