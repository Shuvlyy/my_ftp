/*
** EPITECH PROJECT, 2024
** CHAR_H_
** File description:
** CHAR's header
** Author: lysandre.boursette@epitech.eu
*/

#ifndef CHAR_H_
    #define CHAR_H_

    #include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

    bool sh_is_alpha(char c);
    bool sh_is_numeric(char c);
    bool sh_is_alphanumeric(char c);

#ifdef __cplusplus
}
#endif

#endif
