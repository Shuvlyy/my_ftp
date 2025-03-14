/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_node_destroy
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include "yml.h"

/**
 * Destroys a node.
 *
 * @param   node    Node to destroy
 */
void yml_node_destroy(yml_node_t *node)
{
    struct yml_node_s *needle = NULL;

    if (node == NULL)
        return;
    if (node->name != NULL)
        free(node->name);
    if (node->value != NULL)
        free(node->value);
    while (!TAILQ_EMPTY(&node->children)) {
        needle = TAILQ_FIRST(&node->children);
        TAILQ_REMOVE(&node->children, needle, entries);
        yml_node_destroy(needle);
    }
    free(node);
}
