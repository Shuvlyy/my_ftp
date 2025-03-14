/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_save
** Author: lysandre.boursette@epitech.eu
*/

#include <stdio.h>
#include "yml.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

/**
 * Writes the content of a node in a file, with the
 * right indentation.
 *
 * @param   node    Node to write
 * @param   file    File to write the node in
 * @param   depth   Indentation depth
 */
static
void write_node(yml_node_t *node, FILE *file, int depth)
{
    struct yml_node_s *needle = TAILQ_FIRST(&node->children);

    for (int k = 0; k < depth * NESTING_SPACES; k++)
        fprintf(file, " ");
    if (node->is_list)
        fprintf(file, "- %s%s\n",
            node->name, needle == NULL ? "" : ":");
    else {
        fprintf(file, "%s:", node->name);
        if (node->value != NULL)
            fprintf(file, " %s", node->value);
        fprintf(file, "\n");
    }
    TAILQ_FOREACH(needle, &node->children, entries) {
        write_node(needle, file, depth + 1);
    }
}

/**
 * Saves the current state of a YML instance in a file.
 * If the file doesn't exist, the file is created. Otherwise, the
 * file is overwritten.
 * NOTE: Comments aren't kept.
 *
 * @param   yml         YML instance
 * @param   filepath    File path of the new file
 * @return  SH_EXIT_SUCCESS on success, otherwise SH_EXIT_FAILURE
 */
int yml_save(yml_t *yml, const char *filepath)
{
    FILE *file = fopen(filepath, "w+");
    struct yml_node_s *node = NULL;

    if (file == NULL)
        return sh_put_ierr(FILE_NOT_FOUND);
    TAILQ_FOREACH(node, &yml->nodes, entries) {
        write_node(node, file, 0);
    }
    fclose(file);
    return SH_EXIT_SUCCESS;
}
