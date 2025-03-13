/*
** EPITECH PROJECT, 2024
** STRING_H_
** File description:
** String library header
** Author: lysandre.boursette@epitech.eu
*/

#ifndef STRING_H_
    #define STRING_H_

    #include <stdbool.h>
    #include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

    ssize_t sh_put_str(char const *str);
    size_t sh_str_len(char const *str);
    int sh_str_cmp(char const *s1, char const *s2);
    int sh_str_ncmp(char const *s1, char const *s2, int n);
    char *sh_str_cpy(char *dest, char const *src);
    char *sh_str_ncpy(char *dest, const char *src, int n);
    char *sh_str_cat(char *dest, char const *src);
    // ncat
    char *sh_str_dup(char const *src);
    char **sh_str_split(char *str, char *delims, bool multi);
    bool sh_str_contains(char const *str, char c);
    void sh_remove_trailing_spaces(char *str);
    char *sh_multitok(char *input, char *delimiter);
    char *sh_strstr(char *str, char *delim);
    bool sh_str_endswith(char *str, char *ends_with);
    bool sh_is_str_numeric(char *str, bool count_minuses, bool count_dots);

#ifdef __cplusplus
}
#endif

#endif
