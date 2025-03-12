/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_parsing_update_path
** Author: lysandre.boursette@epitech.eu
*/

#include <stddef.h>
#include <malloc.h>
#include "yml.h"
#include "shuvlib/error.h"
#include "shuvlib.h"
#include "shuvlib/memory.h"

/**
 * Returns the size of the final path.
 *
 * @param   path    Current path
 * @param   n       Path depth to keep
 * @return  Size of the final path
 */
static
size_t get_result_size(const char *path, size_t n)
{
    size_t counter = 0;
    size_t size = 0;

    if (path == NULL || n == 0)
        return 0;
    for (size_t k = 0; path[k] != '\0' && counter < n; k++) {
        if (path[k] == '.')
            counter++;
        if (counter < n)
            size++;
    }
    return size;
}

/**
 * Updates the path used for nesting tracking
 * during parsing.
 *
 * @param   parsing     Parsing instance
 * @param   n           Path depth to keep
 */
void yml_parsing_update_path(yml_parsing_t *parsing, size_t n)
{
    size_t result_size = get_result_size(parsing->path, n);
    char *buf;

    if (parsing->path == NULL) {
        parsing->path = sh_calloc((result_size + 1) * sizeof(char), 0);
        return;
    }
    buf = realloc(
        parsing->path, (result_size + 1) * sizeof(char));
    if (buf == NULL) {
        sh_put_verr(MALLOC_FAIL);
        return;
    }
    parsing->path = buf;
    parsing->path[result_size] = '\0';
}
