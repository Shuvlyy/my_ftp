/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_destroy
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include <stddef.h>
#include "yml.h"

/**
 * Destroys a created YML instance.
 *
 * @param   yml     YML instance
 */
void yml_destroy(yml_t *yml)
{
    struct yml_node_s *needle = NULL;

    if (yml == NULL)
        return;
    if (yml->raw_content != NULL)
        free(yml->raw_content);
    while (!TAILQ_EMPTY(&yml->nodes)) {
        needle = TAILQ_FIRST(&yml->nodes);
        TAILQ_REMOVE(&yml->nodes, needle, entries);
        yml_node_destroy(needle);
    }
    free(yml);
}
