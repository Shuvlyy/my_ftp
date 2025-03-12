/*
** EPITECH PROJECT, 2024
** SH_IS_ALPHA
** File description:
** Returns true if char is alpha
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/char.h"

bool sh_is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z');
}
