##
## EPITECH PROJECT, 2025
## FLAGS_MK
## File description:
## Flags for Makefile
##

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -MMD -MP

CFLAGS += -iquote include
CFLAGS += -iquote shuvlib/include

LDFLAGS := -L shuvlib
LDFLAGS += -lshuv
