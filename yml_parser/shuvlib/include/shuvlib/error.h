/*
** EPITECH PROJECT, 2024
** ERROR_H_
** File description:
** Error library header
** Author: lysandre.boursette@epitech.eu
*/

#ifndef ERROR_H_
    #define ERROR_H_

    #include <stdbool.h>

int sh_put_ierr(char const *err);
void *sh_put_nerr(char const *err);
void sh_put_verr(char const *err);
bool sh_put_berr(char const *err);

#endif /* ERROR_H_ */
