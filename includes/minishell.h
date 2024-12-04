/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/04 16:39:43 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structs.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''

// cleanup.c
void		free_keyval(t_keyval *pair);
int			cleanup(t_data *data);
// env.c
t_keyval	*create_keyval_pair(char *raw, char *key, char *value);
char		*get_value(char *equal_pos);
t_keyval	*get_keyval_pair(char *current_env);
void		add_keyval_to_list(t_keyval **env_list, t_keyval *new_env);
void		get_env_list(t_data *data, char **envp);

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