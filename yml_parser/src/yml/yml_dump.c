/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_dump
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include <sys/queue.h>
#include "yml.h"

/**
 * Prints out the content of a YML instance.
 *
 * @param   yml     YML instance
 */
void yml_dump(yml_t *yml)
{
    struct yml_node_s *node = NULL;

    printf("YML dump\n\n");
    printf("Raw content:\n");
    printf("```yml\n");
    printf("%s\n", yml->raw_content);
    printf("```\n\n");
    printf("Nodes:\n");
    TAILQ_FOREACH(node, &yml->nodes, entries) {
        yml_node_dump(node, 1);
    }
}
