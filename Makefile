NAME := minishell
# includes
INC_DIR := includes
INC := $(INC_DIR)/minishell.h $(INC_DIR)/structs.h
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
# define src dirs
SRC_DIR := src
OBJS_DIR := obj
# define src files
ENV := env env2
EXECUTION := cmd_paths_utils execute_child_process execute hdl_redirs_utils \
			heredoc_utils
MAIN := cleanup error main signals
PARSING := exec_list expander lexer parser
PARSING_TOOLS := helpers token_list utils_exec_list utils_expander \
				utils_expander2 utils_lexer utils_parser
# BUILTIN := echo cd pwd export unset env exit
SRC := $(addsuffix .c, $(addprefix $(SRC_DIR)/env/, $(ENV))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/execution/, $(EXECUTION))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/main/, $(MAIN))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/parsing/, $(PARSING))) \
		$(addsuffix .c, $(addprefix $(SRC_DIR)/parsing_tools/, $(PARSING_TOOLS)))
# replace 'src/' with 'obj/' to get obj file paths
OBJS := $(SRC:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)
# create obj subdirs
OBJS_SUBDIRS := $(sort $(dir $(OBJS)))
$(OBJS_SUBDIRS):
	@mkdir -p $@
# compiler
CC := gcc
CFLAGS := -Wall -Wextra -Werror

all: $(OBJS_SUBDIRS) $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(INC)
	@echo "Building $(NAME)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

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
