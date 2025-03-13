/*
** EPITECH PROJECT, 2024
** MEMORY_H_
** File description:
** Memory library header
** Author: lysandre.boursette@epitech.eu
*/

#ifndef MEMORY_H_
    #define MEMORY_H_

    #include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

    char *sh_memcpy(void *dest, const void *src, size_t n);
    void *sh_realloc(void *ptr, size_t size);
    void *sh_memset(void *ptr, int value, size_t n);
    void *sh_calloc(size_t size, int value);

#ifdef __cplusplus
}
#endif

#endif
