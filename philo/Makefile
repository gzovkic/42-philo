NAME = philo
CC = cc
RM = rm -rf

################################################################################
###############                  DIRECTORIES                      ##############
################################################################################

OBJ_DIR = _obj
INC_DIRS := Includes
SRC_DIRS := src
HEADERS = -I 

vpath %.h $(INC_DIRS)
vpath %.c $(SRC_DIRS)

################################################################################
###############                  SOURCE FILES                     ##############
################################################################################


SRC_FILES := main.c fake_libft.c error_checking.c error_checking_utils.c \
			create_structs.c utils.c
SRC := $(addprefix src/, $(SRC_FILES))

################################################################################
###############               OBJECT FILES & RULES                ##############
################################################################################

OBJS := $(addprefix $(OBJ_DIR)/, $(SRC:%.c=%.o))

# Compilation flags and linking options
CFLAGS := -Wall -Wextra -Werror -g -Iinc -MMD -MP $(addprefix -I, $(INC_DIRS))
CFLAGS_SAN := $(CFLAGS) -fsanitize=address -g
LDFLAGS_SAN := -fsanitize=address

# Color definitions for better terminal output
COLOR_RESET = \033[0m
COLOR_GREEN = \033[0;32m
COLOR_BLUE = \033[0;34m
COLOR_CYAN = \033[0;36m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(COLOR_GREEN)Creating $(NAME)...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)
	@echo "$(COLOR_GREEN)Successful Compilation of $(NAME)$(COLOR_RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "$(COLOR_GREEN)Compiling $<...$(COLOR_RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)


%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@echo "$(COLOR_GREEN)Cleaning object files...$(COLOR_RESET)"
	@$(RM) $(OBJS)

fclean: clean
	@echo "$(COLOR_GREEN)Removing $(NAME)...$(COLOR_RESET)"
	@$(RM) $(OBJ_DIR)
	@$(RM) $(NAME)
	@echo "$(COLOR_GREEN)Removed files successfully$(COLOR_RESET)"

re: fclean all

help:
	@echo "Available targets:"
	@echo "  all      - Build minishell (default)"
	@echo "  clean    - Remove object files"
	@echo "  fclean   - Remove all generated files"
	@echo "  re       - Rebuild minishell"

.PHONY: all clean fclean re help coffin