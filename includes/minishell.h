/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/08 18:17:39 by cde-sous         ###   ########.fr       */
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

// checks.c
int		are_quotes_closed(t_token **token_list);
int	is_valid_assignment(t_token **token_list); // to rename maybe
// cleanup.c
void	free_env(t_env *pair);
void	free_tokens(t_token *token);
int		cleanup(t_data *data, int type);
// env.c
t_env	*create_env_pair(char *raw, char *key, char *value, int is_exported);
t_env	*get_env_pair(char *current_env);
void	add_env_pair_to_list(t_env **env_list, t_env *new_env);
void	get_env_list(t_data *data, char **envp);
// expander.c
void	expander(t_data *data);
// helpers.c
char	*get_value(char *equal_pos);
t_token	*get_prev_token(t_token *prev, t_token *current);
int		get_quoted_word_len(char *word);
int		get_word_len(char *word, int flag);
void	epur_token_value(t_token **token);
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
t_token	*replace_assignment_token(t_token **token_list, t_token *current,
		char *key, char *value); // to rename maybe
// utils_lexer.c
int		is_assignment(char *word);
int		is_word(char *word);
int		is_chevron(char *word);
int		get_token_type(char *word);
int	get_type_len(char *word, int type); // to rename maybe
// utils_parser.c
int		is_value_empty(char *value);
void	delete_empty_tokens(t_token **token_list);
void	replace_word_type(t_token **list, t_token **tmp);
void	replace_token_type(t_token **token_list);

#endif
