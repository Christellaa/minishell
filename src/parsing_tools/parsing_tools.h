/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:54:07 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 16:51:01 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_TOOLS_H
# define PARSING_TOOLS_H

# include "../../includes/minishell.h"

// utils_lexer
int		get_word_len(char *word);
int		stop_word_len_at_special_char(char *word, int len);
t_token	*get_prev_token(t_token *prev, t_token *current);
// token_list
t_token	*create_token(int type, char *value, int len, char quote);
void	add_token_to_list(t_token **tokens, t_token *new_token);
void	replace_token_type(t_token **token_list);
char	*combine_tokens(t_token *token_list);
void	remove_empty_tokens(t_token **token_list);
// utils_exec_list
int		add_arg_to_node(t_exec **node, char *value);
int		add_file_to_node(t_exec **node, char *value, int type);
// utils_lexer_type
int		get_token_type(char *word);
int		get_token_type_len(char *word, int type);
// pid
char	*handle_pid(t_data *data);
// utils_expander_lens
int		get_quoted_len(char *value, char quote);
int		get_len_until_quote(char *value);
char	*get_str_before_dollar(char *value, char *dollar_pos);
char	*get_str_after_dollar(char *var);
int		env_var_len(char *var);
// utils_expansion
char	*handle_var_expansion(t_token *token, char *dollar_pos, t_data *data);

#endif
