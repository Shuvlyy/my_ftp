##
## EPITECH PROJECT, 2025
## FLAGS_MK
## File description:
## Flags for Makefile
##

CFLAGS += -Wall
CFLAGS += -Wextra
#CFLAGS += -Werror
CFLAGS += -std=c++20

CFLAGS += -iquote include
CFLAGS += -iquote yml_parser/include
CFLAGS += -iquote yml_parser/shuvlib/include

LDFLAGS += -L yml_parser -lyml
LDFLAGS += -L yml_parser/shuvlib -lshuv

#LDFLAGS += -lncurses
