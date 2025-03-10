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

include $(MK_DIR)/sources.mk
include $(MK_DIR)/flags.mk
include $(MK_DIR)/colors.mk

OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)
DEP := $(OBJ:%.o=$(BUILD_DIR)/%.d)

.SUFFIXES: .d

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) && \
	echo -e $(BOLD) $(BGT_GREEN) "Project successfully built!" $(RESET) || \
	echo -e $(BOLD) $(RED) "Project failed to build." $(RESET)

$(BUILD_DIR)/%.o: %.cpp
	@ mkdir -p $(dir $@)
	@ $(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS) && \
	echo -e $(BOLD) $(BGT_GREEN) "[OK]" $(RESET) $< || \
	echo -e $(BOLD) $(RED) "[FAIL]" $(RESET) $<

clean:
	@ $(RM) $(OBJ) && $(RM) $(DEP) && \
	echo -e $(BOLD) $(BGT_GREEN) "Project successfully cleaned!" $(RESET) || \
	echo -e $(BOLD) $(RED) "Project failed to clean." $(RESET)

fclean: clean
	@ $(RM) $(NAME)
	@ $(RM) -r $(BUILD_DIR)

re: fclean
	@ make all

debug:
	@ $(MAKE) CFLAGS="$(CFLAGS) -g -DDEBUG" all

-include $(DEP)
