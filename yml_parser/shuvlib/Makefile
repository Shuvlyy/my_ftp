##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile for the Shuvlib
##

NAME = libshuv

include sources.mk
include flags.mk

vpath %.c $(VPATH)

BUILD_DIR := .build

OBJ := $(SRC:%.c=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=$(BUILD_DIR)/%.d)

.SUFFIXES: .d

ifneq ($(shell find . -name ".fast"),)
	MAKEFLAGS += -j
endif

## ---------------------- ##
##    Compilation flags   ##
## ---------------------- ##

CFLAGS = -Wall -Wextra
CFLAGS += -I ./include

## ---------------- ##
##    Color codes   ##
## ---------------- ##

BLACK = "\e[30m"   #
RED = "\e[31m"     #
GREEN = "\e[32m"   #
YELLOW = "\e[33m"  #  Standard
BLUE = "\e[34m"    #  colors
MAGENTA = "\e[35m" #
CYAN = "\e[36m"    #
WHITE = "\e[37m"   #

BGT_BLACK = "\e[90m"   #
BGT_RED = "\e[91m"     #
BGT_GREEN = "\e[92m"   #
BGT_YELLOW = "\e[93m"  #  Bright
BGT_BLUE = "\e[94m"    #  colors
BGT_MAGENTA = "\e[95m" #
BGT_CYAN = "\e[96m"    #
BGT_WHITE = "\e[97m"   #

BOLD = "\e[1m"      #
ITALIC = "\e[3m"    #  Text decorations
UNDERLINE = "\e[4m" #

RESET = "\e[0m"

## -------------- ##
##      Rules     ##
## -------------- ##

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

re: fclean all

-include $(DEP)
