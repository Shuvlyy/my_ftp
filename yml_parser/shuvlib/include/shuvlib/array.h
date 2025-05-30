/*
** EPITECH PROJECT, 2024
** ARRAY_H_
** File description:
** Array library header
** Author: lysandre.boursette@epitech.eu
*/

#ifndef ARRAY_H_
    #define ARRAY_H_

    #include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    size_t sh_array_len(void **array);
    void sh_destroy_string_array(char **array);

#ifdef __cplusplus
}
#endif

#endif
