/*
** EPITECH PROJECT, 2024
** SH_GET_NBR
** File description:
** Converts a string to an integer.
** Author: lysandre.boursette@epitech.eu
*/

#include <stdbool.h>
#include <limits.h>

static
int compute_nbr(int output, char nbr, bool *has_overflowed)
{
    if (output > INT_MAX / 10) {
        *has_overflowed = true;
        return -1;
    }
    output *= 10;
    if (output > INT_MAX - (nbr - '0')) {
        *has_overflowed = true;
        return -1;
    }
    output += nbr - '0';
    return output;
}

static
int get_minuses(char const *str)
{
    int k = 0;

    for (; str[k] != '\0'; str++) {
        if (str[k] == '-')
            k++;
        if (str[k] != '+')
            break;
    }
    return k;
}

int sh_get_nbr(char const *nbr)
{
    bool is_negative = get_minuses(nbr) % 2 != 0;
    bool has_seen_positive = false;
    int output = 0;
    bool has_overflowed = false;

    for (int k = 0; nbr[k] != '\0'; k++) {
        if (has_overflowed)
            break;
        if (nbr[k] == '0' && !has_seen_positive)
            continue;
        if (nbr[k] >= '0' && nbr[k] <= '9') {
            has_seen_positive = true;
            output = compute_nbr(output, nbr[k], &has_overflowed);
            continue;
        }
    }
    output = is_negative ? -1 : output;
    return output;
}
