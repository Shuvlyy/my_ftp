##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for the YML parser
##

NAME = libyml

vpath %.c $(VPATH)

BUILD_DIR := .build
MK_DIR := mk
LIB_DIR := shuvlib

include $(MK_DIR)/sources.mk
include $(MK_DIR)/flags.mk
include $(MK_DIR)/colors.mk

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=$(BUILD_DIR)/%.d)

.SUFFIXES: .d

CC = gcc

## -------------- ##
##      Rules     ##
## -------------- ##

all: shuvlib $(NAME)

shuvlib:
	@ echo -e $(YELLOW) "Building Shuvlib..." $(RESET)
	@ make -s -C $(LIB_DIR)

$(NAME): $(OBJ)
	@ ar rc $(NAME).a $(OBJ) && \
	echo -e $(BGT_GREEN) "YAML library successfully built!" $(RESET) || \
	echo -e $(RED) "YAML library failed to build." $(RESET)

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS) && \
	echo -e $(BOLD) $(BGT_GREEN) "[OK]" $(RESET) $< || \
	echo -e $(BOLD) $(RED) "[FAIL]" $(RESET) $<

clean:
	@ $(RM) $(OBJ) && $(RM) $(DEP) && \
	echo -e $(BGT_GREEN) "YAML library successfully cleaned!" $(RESET) || \
	echo -e $(RED) "YAML library failed to clean." $(RESET)
	@ make -s -C $(LIB_DIR) clean

fclean: clean
	@ $(RM) $(NAME).a
	@ $(RM) -r $(BUILD_DIR)
	@ $(RM) test
	@ make -s -C $(LIB_DIR) fclean

re: fclean
	@ make -s -C $(LIB_DIR) fclean
	@ make all

tests_run: re
	@ gcc -o test tests/test.c -I include -I shuvlib/include \
		-L . -lyml -L shuvlib -lshuv

.PHONY: all shuvlib clean fclean re tests_run

-include $(DEP)
