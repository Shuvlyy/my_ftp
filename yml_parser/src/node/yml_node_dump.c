/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_node_dump
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include "yml.h"

/**
 * Prints out the content of a node.
 *
 * @param   node    Node to display
 * @param   depth   Nesting depth
 */
void yml_node_dump(yml_node_t *node, int depth)
{
    struct yml_node_s *needle = TAILQ_FIRST(&node->children);

    for (int k = 0; k < depth * NESTING_SPACES; k++)
        printf(" ");
    if (node->is_list)
        printf("- %s%s\n",
            node->name, needle == NULL ? "" : ":");
    else {
        printf("%s:", node->name);
        if (node->value != NULL)
            printf(" %s", node->value);
        printf("\n");
    }
    TAILQ_FOREACH(needle, &node->children, entries) {
        yml_node_dump(needle, depth + 1);
    }
}
