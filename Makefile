NAME := minishell

INC_DIR := includes
LIBFT_DIR := libft
SRC_DIR := src
OBJS_DIR := obj

INC := $(INC_DIR)/minishell.h $(INC_DIR)/structs.h $(SRC_DIR)/builtin/builtin.h \
		$(SRC_DIR)/env/env.h $(SRC_DIR)/execution/execution.h \
		$(SRC_DIR)/parsing/parsing.h $(SRC_DIR)/parsing_tools/parsing_tools.h
LIBFT := $(LIBFT_DIR)/libft.a

ENV := env env2 create_path env_utils env_utils2 shlvl shlvl_utils
EXECUTION := cmd_paths_utils child_process execution redirs_utils \
			heredoc_utils exec_utils
MAIN := cleanup error main signals
PARSING := exec_list expander lexer parser
PARSING_TOOLS := utils_lexer utils_lexer_types token_list utils_exec_list \
				utils_expander_lens utils_expansion pid 
BUILTIN := builtin ft_exit ft_cd ft_pwd ft_env ft_export ft_export_utils \
			ft_unset ft_echo
SRC := $(addsuffix .c, $(addprefix $(SRC_DIR)/env/, $(ENV))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/execution/, $(EXECUTION))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/parsing_tools/, $(PARSING_TOOLS))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/builtin/, $(BUILTIN)))

OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

OBJS_SUBDIRS := $(sort $(dir $(OBJS)))

CC := gcc
CFLAGS := -Wall -Wextra -Werror

all: $(OBJS) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(INC)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(OBJS_DIR):
	@mkdir -p $@

$(OBJS_SUBDIRS): $(OBJS_DIR)
	@mkdir -p $@

$(OBJS_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJS_SUBDIRS)
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
