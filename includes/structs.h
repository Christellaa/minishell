/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:14:38 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 13:37:37 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "minishell.h"

typedef enum s_token_type
{
	INFILE = 0,
	HEREDOC,
	TRUNC,
	APPEND,
	FILENAME,
	PIPE,
	ARG,
	WORD
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char quote; // if word has double, single or no quote
	struct s_token	*next;
}					t_token;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}					t_arg;

typedef struct s_files
{
	char			*value;
	t_token_type	type;
	struct s_files	*next;
}					t_files;

typedef struct s_exec
{
	t_arg			*arg_list;
	t_files			*files;
	pid_t			pid;
	int				pipefd[2];
	struct s_exec	*next;
}					t_exec;

typedef struct s_env
{
	char			*raw;
	char			*key;
	char			*value;
	int				is_exported;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_token			*token_list;
	t_exec			*exec_list;
	int				exit_code;
	t_env			*env_list;
}					t_data;

#endif
