/*
** EPITECH PROJECT, 2023
** SH_STR_CMP
** File description:
** Returns the difference between two strings.
** Replicate of the libC "strcmp" function.
** Author: lysandre.boursette@epitech.eu
*/

int sh_str_cmp(char const *s1, char const *s2)
{
    while (*s1 == *s2 && *s1 != 0 && *s2 != 0) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
