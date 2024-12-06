/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/06 16:41:19 by cde-sous         ###   ########.fr       */
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
# define FORBIDDEN_CHARS ";:&(){}[]\\!*" // ? without $ before, ||
// a voir pour le \ si dans " ou ' c'est autorisé

// cleanup.c
void		free_keyval(t_keyval *pair);
int			cleanup(t_data *data);
// env.c
t_keyval	*create_keyval_pair(char *raw, char *key, char *value,
				int is_exported);
char		*get_value(char *equal_pos);
t_keyval	*get_keyval_pair(char *current_env);
void		add_keyval_to_list(t_keyval **env_list, t_keyval *new_env);
void		get_env_list(t_data *data, char **envp);
// checks.c
int			check_forbidden_input(char *word);
// token_list.c
int			get_token_type(char *word);
int			get_type_len(char *word, int type);
t_token		*create_token(int type, char *value, int len);
void		add_token_to_list(t_token **tokens, t_token *new_token);
// lexer.c
int			is_word(char *word);
int			is_chevron(char *word);
int			tokenize(t_token **tokens, char *word);
char		*extract_word(char *input);
void		lexer(t_data *data, char *input);

#endif

/*

lexer:
- if \n : NEWLINE
- if \t or ' ' : discard spaces and tabs
- if < : INFILE
- if << : HEREDOC
- if > : TRUNC
- if >> : APPEND
- if | : PIPE
- if & => PAS GERER
- if || => PAS GERER
- if ; => PAS GERER

*/