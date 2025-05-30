/*
** EPITECH PROJECT, 2024
** xml_parser
** File description:
** xml_create_from_file
** Author: lysandre.boursette@epitech.eu
*/

#include "yml.h"
#include "shuvlib/file.h"
#include "shuvlib/error.h"
#include "shuvlib.h"

/**
 * Creates an YML instance from a file path.
 *
 * @param   filepath    File path
 * @return  Created YML instance
 * @throws  NULL        Malloc failure or YML parsing fail.
 */
yml_t *yml_create_from_file(const char *filepath)
{
    char *file_content;
    yml_t *yml = NULL;

    if (filepath == NULL || filepath[0] == '\0') {
        return NULL;
    }
    file_content = sh_read_file((char *) filepath);
    if (file_content == NULL)
        return sh_put_nerr(MALLOC_FAIL);
    yml = yml_create_from_string(file_content);
    yml->filepath = filepath;
    return yml;
}
