/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/06 16:18:01 by cde-sous         ###   ########.fr       */
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

// helpers.c
t_token		*get_prev_token(t_token *prev, t_token *current);
// cleanup.c
void		free_keyval(t_keyval *pair);
int			cleanup(t_data *data, int type);
// utils.c
char		*get_value(char *equal_pos);
void		epur_token_value(t_token **token);
int			is_value_empty(char *value);
void		delete_empty_quotes(t_token **token_list);
void		determine_token_type(t_token **list, t_token **tmp);
// env.c
t_keyval	*create_keyval_pair(char *raw, char *key, char *value,
				int is_exported);
t_keyval	*get_keyval_pair(char *current_env);
void		add_keyval_to_list(t_keyval **env_list, t_keyval *new_env);
void		get_env_list(t_data *data, char **envp);
// checks.c
int			check_quotes_close(t_token *token);
int			check_assignment(t_token **token_list);
int			check_chevrons(t_token *token);
int			check_double_pipe(t_token *token);
// parser.c
int			check_token_list(t_token **token_list, int err);
int			parser(t_data *data);
// utils_lexer.c
int			get_token_type(char *word);
int			get_word_len(char *word);
int			get_type_len(char *word, int type);
// token_list.c
t_token		*create_token(int type, char *value, int len);
void		add_token_to_list(t_token **tokens, t_token *new_token);
t_token		*replace_assignment_token(t_token **token_list, t_token *current,
				char *key, char *value);
// lexer.c
int			is_assignment(char *word);
int			is_word(char *word);
int			is_chevron(char *word);
int			tokenize(t_token **tokens, char *word);
char		*extract_word(char *input);
void		lexer(t_data *data, char *input);

#endif
