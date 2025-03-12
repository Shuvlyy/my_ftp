/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_find_node_from_path
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include "yml.h"
#include "shuvlib/array.h"
#include "shuvlib/string.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

/**
 * Searches at YML's root.
 *
 * @param   nodes   Nodes to search in
 * @param   search  Search path
 */
static
yml_node_t *get_node_by_name_root(struct yml_list_s *nodes, const char *search)
{
    struct yml_node_s *needle = NULL;

    TAILQ_FOREACH(needle, nodes, entries) {
        if (sh_str_cmp(needle->name, search) == 0)
            return needle;
    }
    return NULL;
}

/**
 * Searches in a node.
 *
 * @param   nodes   Nodes to search in
 * @param   search  Search path
 */
static
yml_node_t *get_node_by_name_node(struct yml_node_list_s *nodes, const char *search)
{
    struct yml_node_s *needle = NULL;

    TAILQ_FOREACH(needle, nodes, entries) {
        if (sh_str_cmp(needle->name, search) == 0)
            return needle;
    }
    return NULL;
}

/**
 * Finds a node from a given path.
 * A path can be the sole name of a node (which must then be at yml's root),
 * or a path to a node using "." as links.
 *
 * Examples:
 *      - "name"
 *      - "person.identity.name"
 *      - ...
 *
 * @param   yml     YML instance
 * @param   search  Search path
 * @returns Found node, NULL if no node were found.
 */
yml_node_t *yml_find_node_from_path(yml_t *yml, const char *search)
{
    char **split = sh_str_split((char *) search, ".", false);
    size_t split_len = 0;
    struct yml_node_s *needle = NULL;

    if (split == NULL)
        return sh_put_nerr(MALLOC_FAIL);
    split_len = sh_array_len((void **) split);
    for (size_t k = 0; k < split_len; k++) {
        if (needle == NULL)
            needle = get_node_by_name_root(&yml->nodes, split[k]);
        else
            needle = get_node_by_name_node(&needle->children, split[k]);
        if (needle == NULL)
            break;
    }
    sh_destroy_string_array(split);
    return needle;
}
