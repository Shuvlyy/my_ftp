##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for the Shuvlib
##

NAME = libshuv

vpath %.c $(VPATH)

BUILD_DIR := .build
MK_DIR := mk

include $(MK_DIR)/flags.mk
include $(MK_DIR)/sources.mk
include $(MK_DIR)/colors.mk

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=$(BUILD_DIR)/%.d)

.SUFFIXES: .d

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME).a $(OBJ) && \
	echo -e $(BOLD) $(BGT_GREEN) "Shuvlib successfully built!" $(RESET) || \
	echo -e $(BOLD) $(RED) "Shuvlib failed to build." $(RESET)

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS) && \
	echo -e $(BOLD) $(BGT_GREEN) "[OK]" $(RESET) $< || \
	echo -e $(BOLD) $(RED) "[FAIL]" $(RESET) $<

clean:
	@$(RM) $(OBJ) && $(RM) $(DEP) && \
	echo -e $(BOLD) $(BGT_GREEN) "Shuvlib successfully cleaned!" $(RESET) || \
	echo -e $(BOLD) $(RED) "Shuvlib failed to clean." $(RESET)

fclean: clean
	@$(RM) $(NAME).a
	@ $(RM) -r $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
