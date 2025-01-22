/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/19 14:48:16 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

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

// cleanup.c
void			free_env(t_env *pair);
void			free_tokens(t_token *token);
void			free_exec(t_exec *exec);
void			print_error(int flag, char *error, char *option);
void			cleanup(t_data *data, int type);
// env.c
t_env			*create_env_node(char *raw, char *key, char *value,
					int show_in_env);
t_env			*get_env_pair(char *current_env);
void			add_env_node_to_list(t_env **env_list, t_env *new_env);
void			create_env_list(t_data *data, char **envp);
// exec_list.c
void			create_exec_node(t_exec **new_node);
void			add_value_to_node(t_exec **node, char *value, int type);
void			add_node_to_list(t_exec **exec_list, t_exec *node);
int				create_and_add_node_to_list(t_data *data, t_exec **new_node);
int				create_exec_list(t_data *data);
// expander.c
char			*fetch_env_value(char *pos, t_data *data, int *to_split);
char			*handle_expansion(char *pos, t_data *data, int *to_split,
					char quote);
char			*search_quote_and_join_until_dollar(char *pos, char **copy,
					char *quote, t_token **token);
int				expand_when_dollar(t_token **token, t_data *data, char quote);
int				expander(t_data *data);
// helpers.c
char			*get_value(char *equal_pos);
t_token			*get_prev_token(t_token *prev, t_token *current);
char			has_quote(char quote, char current_char);
int				get_word_len(char *word, int flag);
char			*ft_strjoin_free_both(char *s1, char *s2);
// lexer.c
int				tokenize(t_token **tokens, char *word);
char			*extract_word(char *input);
int				lexer(t_data *data, char *input);
// parser.c
void			delete_token_chevron(t_token **list, t_token *current,
					t_token **next);
int				is_order_valid(t_token **list, t_token *current,
					t_token **next);
int				validate_pipeline(t_token **token_list);
int				parser(t_data *data, char *input);
// signals.c
void			sig_int_quit(int code);
void			handle_signals(void);
// token_list.c
t_token			*create_token(int type, char *value, int len);
void			add_token_to_list(t_token **tokens, t_token *new_token);
int				create_and_add_token(t_token **cur_token, char *copy,
					char **split);
int				split_token(char *expanded, t_token **cur_token, char *copy,
					char *tmp);
// utils_exec_list.c
t_arg			*find_last_arg(t_arg *arg);
t_redirs		*find_last_redir(t_redirs *redir);
void			add_arg_to_node(t_exec **node, char *value);
void			add_redir_to_node(t_exec **node, char *value, int type);
// utils_expander.c
char			*init_copy(t_token **cur_token);
char			*get_env_var(char *var_name, t_env *env);
void			search_quote(char *quote, char *copy, int len);
void			join_until_dollar(t_token **cur_token, char *copy, int len);
// utils_expander2.c
int				can_split(t_token *token_list, t_token *cur_token, int to_split,
					char quote);
char			*join_str_without_external_quotes(char *value, char quote);
int				remove_external_quotes(t_token **token);
// utils_lexer.c
int				is_word(char *word);
int				is_chevron(char *word);
int				get_token_type(char *word);
int				get_type_len(char *word, int type);
// utils_parser.c
int				is_value_empty(char *value);
void			delete_empty_tokens(t_token **token_list);
void			replace_token_type(t_token **token_list);
int				var_name_len(char *value);

#endif
