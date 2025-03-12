/*
** EPITECH PROJECT, 2024
** yml_parser
** File description:
** yml_create_from_string
** Author: lysandre.boursette@epitech.eu
*/

#include <malloc.h>
#include "yml.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

/**
 * Creates an YML instance from a string (YML content).
 *
 * @param   string  YML content
 * @return  Created YML instance
 * @throws  NULL    Malloc failure or YML parsing fail.
 */
yml_t *yml_create_from_string(char *string)
{
    yml_t *yml = malloc(sizeof(yml_t));

    if (yml == NULL)
        return sh_put_nerr(MALLOC_FAIL);
    yml->raw_content = string;
    TAILQ_INIT(&yml->nodes);
    if (yml_parse(yml) == SH_EXIT_FAILURE)
        return yml_destroy(yml), sh_put_nerr(YML_PARSING_FAIL);
    return yml;
}
