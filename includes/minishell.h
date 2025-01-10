/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/10 16:29:17 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

// cleanup.c
void	free_env(t_env *pair);
void	free_tokens(t_token *token);
int		cleanup(t_data *data, int type);
// exec_list.c
t_exec	*create_exec_node(void);
void	add_value_to_node(t_exec **node, char *value, int type);
void	add_node_to_list(t_exec **exec_list, t_exec *node);
int		create_and_add_node_to_list(t_data *data, t_exec *new_node);
int		create_exec_list(t_data *data);
// env.c
t_env	*create_env_node(char *raw, char *key, char *value, int is_exported);
t_env	*get_env_pair(char *current_env);
void	add_env_node_to_list(t_env **env_list, t_env *new_env);
void	create_env_list(t_data *data, char **envp);
// expander.c
char	*get_env_var(char *var_name, t_env *env);
void	replace_var_name(char *start, t_data *data, char **expanded,
			char quote);
void	expand_var(t_token **tmp, t_data *data);
void	remove_external_quotes(t_token **token);
void	expander(t_data *data);
// helpers.c
char	*get_value(char *equal_pos);
t_token	*get_prev_token(t_token *prev, t_token *current);
char	has_quote(char quote, char current_char);
int		get_word_len(char *word, int flag);
char	*ft_strjoin_free_both(char *s1, char *s2);
// lexer.c
int		tokenize(t_token **tokens, char *word);
char	*extract_word(char *input);
int		lexer(t_data *data, char *input);
// parser.c
int		is_order_valid(t_token *list, t_token *current, t_token *next);
int		validate_pipeline(t_token *token_list);
int		parser(t_data *data);
// token_list.c
t_token	*create_token(int type, char *value, int len);
void	add_token_to_list(t_token **tokens, t_token *new_token);
// utils_lexer.c
int		is_word(char *word);
int		is_chevron(char *word);
int		get_token_type(char *word);
int		get_type_len(char *word, int type);
// utils_parser.c
int		is_value_empty(char *value);
void	delete_empty_tokens(t_token **token_list);
void	replace_token_type(t_token **token_list);
int		var_name_len(char *value);
char	*epur_token_value(char *value);

#endif
