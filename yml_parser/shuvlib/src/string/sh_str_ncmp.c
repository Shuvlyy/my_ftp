/*
** EPITECH PROJECT, 2024
** SH_STR_NCMP
** File description:
** Same as sh_str_cmp, but for the n first characters.
** Author: lysandre.boursette@epitech.eu
*/

int sh_str_ncmp(char const *s1, char const *s2, int n)
{
    while (n && *s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0 || *s1 == *s2)
        return 0;
    return *s1 - *s2;
}
