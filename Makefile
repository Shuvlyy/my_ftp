##
## EPITECH PROJECT, 2025
## MAKEFILE
## File description:
## Makefile for my_ftp project
##

NAME = myftp

vpath %.cpp $(VPATH)

BUILD_DIR := .build
MK_DIR := mk
LIBYML_DIR := yml_parser

include $(MK_DIR)/sources.mk
include $(MK_DIR)/flags.mk
include $(MK_DIR)/colors.mk

OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

CC = g++

all: libyml $(NAME)

$(NAME): $(OBJ)
	@ $(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) && \
	echo -e $(BOLD) $(BGT_GREEN) "Project successfully built!" $(RESET) || \
	echo -e $(BOLD) $(RED) "Project failed to build." $(RESET)

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) -o $@ -c $< $(CFLAGS) $(LDFLAGS) && \
	echo -e $(BOLD) $(BGT_GREEN) "[OK]" $(RESET) $< || \
	echo -e $(BOLD) $(RED) "[FAIL]" $(RESET) $<

clean:
	@ $(MAKE) -s -C $(LIBYML_DIR) clean && \
	$(RM) $(OBJ) && \
	echo -e $(BOLD) $(BGT_GREEN) "Project successfully cleaned!" $(RESET) || \
	echo -e $(BOLD) $(RED) "Project failed to clean." $(RESET)

fclean: clean
	@ $(RM) $(NAME)
	@ $(RM) -r $(BUILD_DIR)
	@ $(MAKE) -s -C $(LIBYML_DIR) fclean

re: fclean
	@ $(MAKE) all

libyml:
	@ $(MAKE) -s -C yml_parser all

debug:
	@ $(MAKE) CFLAGS="$(CFLAGS) -DDEBUG" all

.PHONY: all libyml clean fclean re tests_run
