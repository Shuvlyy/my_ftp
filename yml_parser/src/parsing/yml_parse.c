/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_parse
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include "yml.h"
#include "shuvlib/string.h"
#include "shuvlib/array.h"
#include "shuvlib/error.h"
#include "shuvlib.h"
#include "shuvlib/memory.h"

/**
 * Used for comment check and empty lines check.
 *
 * @param   needle  Where the parser is
 */
static
bool should_skip_line(char *needle)
{
    if (*needle == '\0')
        return true;
    for (; *needle == ' '; needle++);
    return *needle == '#' || *needle == '\0';
}

/**
 * Checks for line error.
 * Returns true if an error has been spotted.
 *
 * @param   split       Split content
 * @param   split_len   Split content size
 */
static
bool check_line_error(char **split, size_t split_len)
{
    (void) split;
    if (split_len == 0 || split_len > 2)
        return true;
    return false;
}

/**
 * Returns true if current line is an object.
 * Otherwise returns false (is object is a list).
 *
 * @param   name    Node name
 * @param   needle  Current line
 * @return  True if current line is an object.
 */
static
bool is_object(char *name, char *needle)
{
    char n[MAX_STRING_LEN] = { 0 };
    size_t name_len = sh_str_len(name);

    sh_str_cpy(n, name);
    n[name_len] = ':';
    n[name_len + 1] = '\0';
    return sh_strstr(needle, n);
}

/**
 * Creates a new path, for parsing's sake.
 *
 * @param   node        Current node
 * @param   parsing     Parsing structure
 * @return  Created path
 */
static
char *concat_new_path(yml_node_t *node, yml_parsing_t *parsing)
{
    char *buf = NULL;

    buf = sh_calloc(
        sh_str_len(parsing->path) + sh_str_len(node->name) + 2, 0);
    if (buf == NULL)
        return NULL;
    sprintf(buf, "%s%s%s", parsing->path,
        (parsing->path != NULL && parsing->path[0] != '\0') ? "." : "",
        node->name);
    parsing->path = buf;
    return buf;
}

/**
 * Places the node in the right context.
 *
 * @param   node        Node to place
 * @param   parsing     Parsing structure
 */
static
void place_node(yml_node_t *node, size_t spaces, yml_parsing_t *parsing)
{
    yml_node_t *parent = NULL;
    size_t depth = spaces / NESTING_SPACES;

    yml_parsing_update_path(parsing, depth);
    if (parsing->path != NULL && parsing->path[0] != '\0')
        parent = yml_find_node_from_path(parsing->main, parsing->path);
    if (node->value == NULL && is_object(node->name, parsing->needle))
        if (concat_new_path(node, parsing) == NULL)
            return;
    if (parent == NULL)
        TAILQ_INSERT_TAIL(&parsing->main->nodes, node, entries);
    else
        TAILQ_INSERT_TAIL(&parent->children, node, entries);
}

/**
 * Line parsing.
 *
 * @param   needle              Where the parser is
 * @param   parsing             Parsing structure
 * @returns SH_EXIT_SUCCESS     OK
 * @returns SH_EXIT_FAILURE     Parsing failure
 */
static
int parse_line(yml_parsing_t *parsing)
{
    char **split = NULL;
    size_t split_len = 0;
    size_t spaces = 0;
    yml_node_t *node = NULL;

    for (; parsing->needle[spaces] == ' '; spaces++);
    split = sh_str_split(parsing->needle, ":", false);
    if (split == NULL)
        return sh_put_ierr(MALLOC_FAIL);
    split_len = sh_array_len((void **) split);
    if (check_line_error(split, split_len))
        return sh_destroy_string_array(split), sh_put_ierr(YML_WRONG_SYNTAX);
    node = yml_node_create(split[0], split[1]);
    if (node == NULL)
        return sh_destroy_string_array(split), sh_put_ierr(MALLOC_FAIL);
    place_node(node, spaces, parsing);
    sh_destroy_string_array(split);
    return SH_EXIT_SUCCESS;
}

/**
 * Parses the YML content into the YML instance.
 *
 * @param   yml                 YML instance
 * @returns SH_EXIT_SUCCESS     OK
 * @returns SH_EXIT_FAILURE     Parsing failure
 */
int yml_parse(yml_t *yml)
{
    char **split = sh_str_split(yml->raw_content, "\n\0", false);
    size_t split_len = sh_array_len((void **) split);
    yml_parsing_t parsing = { 0 };
    int status = SH_EXIT_SUCCESS;

    if (split == NULL)
        return sh_put_ierr(YML_CREATION_FAIL);
    yml_parsing_create(&parsing, yml);
    for (size_t k = 0; k < split_len; k++) {
        parsing.needle = split[k];
        if (should_skip_line(parsing.needle))
            continue;
        if (parse_line(&parsing) == SH_EXIT_FAILURE) {
            status = sh_put_ierr(YML_LINE_PARSING_FAIL);
            break;
        }
    }
    yml_parsing_destroy(&parsing);
    return sh_destroy_string_array(split), status;
}
