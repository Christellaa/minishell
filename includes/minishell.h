/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylini <cylini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/31 21:52:55 by cylini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define SYNTAX_ERR "Syntax error near unexpected token"
// ; -> ...token ';' OR | (first or not followed) OR ||
// OR CHEVRON (= 'newline' if no CHEVRON follows, otherwise CHEVRON)
# define CMD_ERR ": command not found"
// abc -> abc: command...
# define OPTION_ERR ": invalid option --"
// ls -z -> ls: invalid option -- 'z'
# define FILE_ERR ": No such file or directory"
// <a (inexistant) -> a: No...
# define FILE_DENY ": Permission denied"
// <a (no permission) -> a: Permission...
# define QUOTE_ERR "Unclosed quote"
# define MALLOC_ERR "Malloc error"
# define TOO_MANY_ARG "Too many arguments. It should be [./minishell]"

extern pid_t	g_signal;

// error.c
int				print_error(int flag, char *error, t_data *data);
// cleanup.c
void			cleanup(t_data *data, int type);
// env.c
t_env			*create_env_node(char *raw, char *key, char *value,
					int show_in_env);
void			add_env_node_to_list(t_env **env_list, t_env *new_env);
int				get_env_list(t_data *data, char **envp);
// env2.c
int				create_env_list(t_data *data);
// exec_list.c
int				create_exec_list(t_data *data);
// expander.c
int				expand_tokens(t_data *data);
// helpers.c
char			*get_env_value(char *equal_pos);
t_token			*get_prev_token(t_token *prev, t_token *current);
char			has_quote(char quote, char current_char);
int				get_word_len(char *word);
int				stop_word_len_at_special_char(char *word, int len);
char			*ft_strjoin_free_both(char *s1, char *s2);
// lexer.c
int				lex_input(char *input, t_data *data);
// parser.c
int				parse_input(t_data *data, char *input);
// signals.c
void			handle_signals(void);
void			handle_child_signals(void);
// token_list.c
t_token			*create_token(int type, char *value, int len);
void			add_token_to_list(t_token **tokens, t_token *new_token);
int				split_token(char *expanded, t_token **token, char *copy,
					char *tmp);
// utils_exec_list.c
int				add_arg_to_node(t_exec **node, char *value);
int				add_file_to_node(t_exec **node, char *value, int type);
// utils_expander.c
char			*init_copy(t_token **token);
char			*get_env_var(char *var_name, t_env *env);
void			search_quote(char *quote, char *copy, int len);
void			join_until_dollar(t_token **token, char *copy, int len);
// utils_expander2.c
int				can_split_token(t_token *token_list, t_token *token,
					int to_split, char quote);
int				remove_external_quotes(t_token **token, t_data *data);
// utils_lexer.c
int				get_token_type(char *word);
int				get_token_type_len(char *word, int type);
// utils_parser.c
void			delete_empty_tokens(t_token **token_list);
void			replace_token_type(t_token **token_list);
int				var_name_len(char *value);
// cmd_paths_utils.c
char			**get_and_split_paths(t_env *env_list);
int				is_absolute_path(char *cmd);
char			*get_relative_path(char *cmd, t_data *data, char **split_paths);
// execute_child_process.c
char			**convert_args_list_to_tab(t_arg *arg_list);
char			**convert_env_list_to_tab(t_env *env_list);
char			*get_cmd_path(char *cmd, t_data *data);
int				execute_child_process(t_exec *exec_node, t_data *data);
// execute.c
int				is_builtin(char *cmd);
int				create_pipes(t_data *data, t_exec *head_exec_list);
int				close_all_pipefds(t_data *data);
int				wait_all_pids(t_exec *head_exec_list);
void			execute(t_data *data);
// hdl_redirs_utils.c
int				handle_redirs(t_data *data, t_exec *exec_node);
int				handle_files(t_data *data, t_exec *exec_node);
// heredoc_utils.c
char			*name_here_doc(char *value, int *i);
void			write_in_heredoc(const char *delimiter, int fd);
int				handle_here_doc(t_data *data, t_exec *node);
int				write_mode_here_doc(t_files *file, int *i, t_data *data);
// builtin.c
int				execute_builtin(int builtin, t_data *data, t_exec *exec_node);
void			check_builtin(t_data *data, t_exec *exec_node);
// // ft_exit.c
void			ft_exit(t_data *data, t_exec *exec_node);
int				ft_cd(t_data *data, t_exec *exec_node);

#endif
