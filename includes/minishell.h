/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:37:23 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:13:13 by cde-sous         ###   ########.fr       */
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
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define IN_ENV 0b01
# define IN_EXPORT 0b10

# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

# define MAX_FD 1024
# define MAX_SHLVL 999
# define FIRST_RUN_FILE "/tmp/minishell_first_run"

# define SYNTAX_ERR "Syntax error near unexpected token"
# define CMD_ERR ": command not found"
# define FILE_ERR ": No such file or directory"
# define FILE_DENY ": Permission denied"
# define QUOTE_ERR "Unclosed quote"
# define MALLOC_ERR "Malloc error"
# define TOO_MANY_ARG "Too many arguments. It should be [./minishell]"

extern pid_t	g_signal;

// error.c
int				print_error(int flag, char *error, t_data *data);
// cleanup.c
void			cleanup(t_data *data, int type);
void			free_env(t_env *pair);

// signals.c
void			handle_parent_signals(void);
void			handle_child_signals(void);

#endif
