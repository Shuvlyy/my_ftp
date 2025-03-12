/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_get_list
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include "yml.h"
#include "shuvlib/memory.h"
#include "shuvlib/string.h"
#include "shuvlib.h"

/**
 * Prints out an error.
 *
 * @param   err     Error
 * @param   path    Node path
 * @return  Default value (0)
 */
static
char **print_err(char *err, char *path)
{
    printf("Error: \"%s\": %s\n", path, err);
    return NULL;
}

/**
 * List getter from node path.
 *
 * @param   yml     YML instance
 * @param   path    Node path
 * @return  Fetched list.
 */
char **yml_get_list(yml_t *yml, char *path)
{
    yml_node_t *node = yml_find_node_from_path(yml, path);
    struct yml_node_s *needle = TAILQ_FIRST(&node->children);
    char **output = NULL;
    int children_n = yml_get_children_n(yml, path);
    int i = 0;

    if (node == NULL)
        return print_err(YML_NODE_NOT_FOUND, path);
    output = sh_calloc((children_n + 1) * sizeof(char *), 0);
    if (output == NULL)
        return print_err(MALLOC_FAIL, path);
    for (; needle; needle = needle->entries.tqe_next) {
        output[i] = sh_str_dup(needle->name);
        i++;
    }
    output[i] = NULL;
    return output;
}
