/*
** EPITECH PROJECT, 2024
** SH_IS_NUMERIC
** File description:
** Returns true if char is numeric
** Author: lysandre.boursette@epitech.eu
*/

#include "shuvlib/char.h"

bool sh_is_numeric(char c)
{
    return c >= '0' && c <= '9';
}
