/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_node_create
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include "yml.h"
#include "shuvlib/string.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

/**
 * Formats the node content:
 *   - Removes trailing spaces
 *   - Removes the beginning "- " if node is the content of a list.
 *
 * @param   node    Node to format
 */
static
void format_node_content(yml_node_t *node)
{
    if (node->name != NULL) {
        sh_remove_trailing_spaces(node->name);
        if (node->is_list)
            memmove(node->name, node->name + 2, sh_str_len(node->name) - 1);
    }
    if (node->value != NULL)
        sh_remove_trailing_spaces(node->value);
}

/**
 * Updates node's data (is_list).
 *
 * @param   node    Node to update
 */
static
void set_is_list(yml_node_t *node)
{
    size_t i = 0;

    for (; node->name[i] == ' '; i++);
    node->is_list = node->name[i] == '-' && node->name[i + 1] == ' ';
}

/**
 * Creates a node with a name and a value.
 *
 * @param   name    Node name
 * @param   value   Node value
 */
yml_node_t *yml_node_create(const char *name, const char *value)
{
    yml_node_t *node = malloc(sizeof(yml_node_t));
    char *k = sh_str_dup(name);
    char *v = sh_str_dup(value);

    if (node == NULL)
        return sh_put_nerr(MALLOC_FAIL);
    node->name = k;
    node->value = v;
    set_is_list(node);
    format_node_content(node);
    TAILQ_INIT(&node->children);
    return node;
}
