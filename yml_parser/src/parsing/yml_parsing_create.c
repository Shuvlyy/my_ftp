/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_parsing_create
** Author: lysandre.boursette@epitech.eu
*/

#include "yml.h"

/**
 * Fills up the parsing structure.
 *
 * @param   parsing     Parsing structure
 * @param   yml         YML instance
 */
void yml_parsing_create(yml_parsing_t *parsing, yml_t *yml)
{
    parsing->main = yml;
    parsing->path = NULL;
    parsing->needle = NULL;
}
