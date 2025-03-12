/*
** EPITECH PROJECT, 2024
** ARRAY_H_
** File description:
** Array library header
** Author: lysandre.boursette@epitech.eu
*/

#pragma once

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t sh_array_len(void **array);
void sh_destroy_string_array(char **array);

#ifdef __cplusplus
}
#endif
