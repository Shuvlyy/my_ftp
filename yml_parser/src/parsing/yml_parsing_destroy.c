/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_parsing_destroy
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include "yml.h"

/**
 * Destroys parsing structure content.
 *
 * @param   parsing     Parsing structure
 */
void yml_parsing_destroy(yml_parsing_t *parsing)
{
    if (parsing->path != NULL)
        free(parsing->path);
}
