/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:14:38 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/04 16:17:33 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum s_error
{
	NEWLINE_ERR, // ?
	QUOTES_ERR,  // quotes not finished
	PIPE_ERR,    // double pipe?
	SKIP_CMD     // when cmd not found/executable
}					t_error;

typedef enum s_token_type
{
	INFILE,  // < infile
	HEREDOC, // << limiter
	TRUNC,   // > outfile
	APPEND,  // >> outfile
	CMD,     // "ls" "echo"
	ARG,
	// "-l" "hello" "$USER" "hello 'world'"
	// "hello \'world\'" "hello "world"" "hello \"world\""
	PIPE // |
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
	char *path;        // file.txt
	t_token_type type; // trunc
	struct s_redirs	*next;
}					t_redirs;

typedef struct s_cmd
{
	char *cmd;        // ls
	t_arg *arg_list;  // -l
	t_redirs *redirs; // pipes, files
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_keyval
{
	char *raw;   // USER=cde-sous
	char *key;   // USER
	char *value; // cde-sous
	struct s_keyval	*next;
}					t_keyval;

typedef struct s_data
{
	t_token			*token_list;
	t_cmd			*cmd_list;
	int nb_cmd;         // to malloc t_cmd
	pid_t *pids;        // parent waiting, signals
	int exit_code;      // last cmd, outfile
	t_keyval *env_list; // environment list
	t_keyval *exp_list; // export list
}					t_data;

#endif