NAME := minishell
NAMEB := checker
SRC := main.c
OBJS_DIR := obj
OBJS := $(SRC:%.c=$(OBJS_DIR)/%.o)
INCLUDES := minishell.h
CC := gcc
CFLAGS := -Wall -Wextra -Werror
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

all: $(OBJS_DIR) $(LIBFT) $(NAME)

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(NAME): $(OBJS) $(INCLUDES)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJS_DIR)/%.o : %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Building $(LIBFT)"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "Removing object files"
	@rm -f $(OBJS)
	@if [ -d $(OBJS_DIR) ]; then rm -rf $(OBJS_DIR); fi
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Removing object files and $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re