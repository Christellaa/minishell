NAME := minishell
NAMEB := checker
SRC_DIR := ./src
SRC := $(SRC_DIR)/main.c $(SRC_DIR)/env.c $(SRC_DIR)/env2.c $(SRC_DIR)/lexer.c \
		$(SRC_DIR)/utils_lexer.c $(SRC_DIR)/token_list.c $(SRC_DIR)/parser.c \
		$(SRC_DIR)/utils_parser.c $(SRC_DIR)/cleanup.c $(SRC_DIR)/error.c \
		$(SRC_DIR)/helpers.c $(SRC_DIR)/expander.c $(SRC_DIR)/utils_expander.c \
		$(SRC_DIR)/utils_expander2.c $(SRC_DIR)/exec_list.c \
		$(SRC_DIR)/utils_exec_list.c $(SRC_DIR)/signals.c $(SRC_DIR)/execute.c
OBJS_DIR := ./obj
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)
INC_DIR := ./includes
INC := $(INC_DIR)/minishell.h $(INC_DIR)/structs.h
CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(OBJS_DIR) $(LIBFT) $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) $(INC)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Building $(LIBFT)"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Removing object files"
	@if [ -d $(OBJS_DIR) ]; then rm -rf $(OBJS_DIR); fi
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing object files and $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
