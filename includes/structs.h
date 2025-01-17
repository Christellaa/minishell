/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:14:38 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 09:10:52 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum s_token_type
{
	INFILE = 0, // <
	HEREDOC,    // <<
	TRUNC,      // >
	APPEND,     // >>
	FILENAME,   // "infile" "Makefile" "outfile"
	PIPE,       // |
	ARG,        // cmd, option, arg
	WORD        // stops at PIPE, CHEVRON, or space
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}					t_arg;

typedef struct s_redirs
{
	char *value;       // file.txt, >
	t_token_type type; // filename, trunc
	struct s_redirs	*next;
}					t_redirs;

typedef struct s_exec
{
	t_arg *arg_list;  // cmd, option, arg: echo, -n, hello
	t_redirs *redirs; // pipes, files
	struct s_exec	*next;
}					t_exec;

typedef struct s_env
{
	char *raw;       // USER=cde-sous
	char *key;       // USER
	char *value;     // cde-sous
	int show_in_env; // if exported, then give to child processes
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_token			*token_list;
	t_exec			*exec_list;
	int nb_cmd;      // useless?
	pid_t *pids;     // parent waiting, signals
	int exit_code;   // last cmd, outfile
	t_env *env_list; // environment & export list
}					t_data;

#endif
