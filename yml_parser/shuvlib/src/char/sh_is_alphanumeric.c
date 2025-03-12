/*
** EPITECH PROJECT, 2024
** SH_IS_ALPHANUMERIC
** File description:
** Returns true if char is alphanumeric
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/char.h"

bool sh_is_alphanumeric(char c)
{
    return sh_is_alpha(c) || sh_is_numeric(c);
}
