/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_get_children_n
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
int print_err(const char *err, const char *path)
{
    fprintf(stderr,"Error: \"%s\": %s\n", path, err);
    return -1;
}

/**
 * Returns the total amount of children of a node.
 *
 * @param   yml     YML instance
 * @param   path    Node path
 * @return  Total amount of children of a node.
 */
int yml_get_children_n(yml_t *yml, const char *path)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    int counter = 0;
    struct yml_node_s *needle = NULL;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    TAILQ_FOREACH(needle, &node->children, entries)
        counter++;
    return counter;
}
