/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:54:07 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 12:55:14 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOOLS_H
# define PARSING_TOOLS_H

# include "../../includes/minishell.h"

// helpers.c
char	*get_env_value(char *equal_pos);
t_token	*get_prev_token(t_token *prev, t_token *current);
char	has_quote(char quote, char current_char);
int		get_word_len(char *word);
int		stop_word_len_at_special_char(char *word, int len);
char	*ft_strjoin_free_both(char *s1, char *s2);
// token_list.c
t_token	*create_token(int type, char *value, int len);
void	add_token_to_list(t_token **tokens, t_token *new_token);
int		split_token(char *expanded, t_token **token, char *copy, char *tmp);
// utils_exec_list.c
int		add_arg_to_node(t_exec **node, char *value);
int		add_file_to_node(t_exec **node, char *value, int type);
// utils_expander.c
char	*init_copy(t_token **token);
char	*get_env_var(char *var_name, t_env *env);
void	search_quote(char *quote, char *copy, int len);
void	join_until_dollar(t_token **token, char *copy, int len);
// utils_expander2.c
int		can_split_token(t_token *token_list, t_token *token, int to_split,
			char quote);
int		remove_external_quotes(t_token **token, t_data *data);
// utils_lexer.c
int		get_token_type(char *word);
int		get_token_type_len(char *word, int type);
// utils_parser.c
void	delete_empty_tokens(t_token **token_list);
void	replace_token_type(t_token **token_list);
int		var_name_len(char *value);

#endif
