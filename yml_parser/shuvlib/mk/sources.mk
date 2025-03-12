##
## EPITECH PROJECT, 2023
## SOURCES_MK
## File description:
## Sources for Makefile
##

VPATH += src/

### STRING ###
SRC += string/sh_str_len.c \
	string/sh_str_cmp.c \
	string/sh_str_ncmp.c \
	string/sh_str_cpy.c \
	string/sh_str_ncpy.c \
	string/sh_put_str.c \
	string/sh_str_cat.c \
	string/sh_str_dup.c \
	string/sh_str_split.c \
	string/sh_str_contains.c \
	string/sh_remove_trailing_spaces.c \
	string/sh_multitok.c \
	string/sh_strstr.c \
	string/sh_str_endswith.c \
	string/sh_is_str_numeric.c

### MEMORY ###
SRC += memory/sh_memcpy.c \
	memory/sh_realloc.c \
	memory/sh_memset.c \
	memory/sh_calloc.c

### FILE ###
SRC += file/sh_read_file.c \
	file/sh_get_file_size.c \
	file/sh_file_exists.c

### ERROR ###
SRC += error/sh_put_ierr.c \
	error/sh_put_nerr.c \
	error/sh_put_berr.c \
	error/sh_put_verr.c

### ARRAY ###
SRC += array/sh_array_len.c \
	array/sh_destroy_string_array.c

### CHAR ###
SRC += char/sh_is_alpha.c \
	char/sh_is_numeric.c \
	char/sh_is_alphanumeric.c
