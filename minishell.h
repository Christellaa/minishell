/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:26:23 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/02 17:04:56 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef enum s_token_type
{
	// EMPTY,   // ligne vide
	CMD,     // "ls"
	ARG,     // "-l"
	APPEND,  // >> outfile
	TRUNC,   // > outfile
	INFILE,  // < infile
	HEREDOC, // << limiter
	PIPE,    // |
}					t_token_type;

typedef struct s_redirection
{
	char *file_path;            // outfile.txt
	t_token_type type;          // trunc (> outfile.txt)
	struct s_redirection *next; // NULL
}					t_redirection;

typedef struct s_exec
{
	char *cmd;                  // "ls"
	char *args;                 // "-l"
	t_redirection redirections; // append, trunc, infile, heredoc, pipe
	struct s_exec *next;        // next cmd
}					t_exec;

typedef struct s_tokens
{
	t_token_type	type;
	char			*value;
	struct s_tokens	*prev;
	struct s_tokens	*next;
}					t_tokens;

// list_tokens
t_tokens			*create_token(int type, char *value);
void				add_token_to_list(t_tokens **tokens, t_tokens *new);
// extract
void				extract_file(t_tokens *token, char *input, int i);

/*
1. pour chaque mot (zappe les espaces) de input, on met le token
	+ la valeur
2. loop de t_data
2.a a chaque type = CMD,
	voir previous (| ou infile ou heredoc) et next (args ou | ou outfile)


--------------------
soit pipe, soit 2 fois a gauche pour avoir redirection infile
--------------------
< Makefile cat | wc -l > outfile.txt
<< EOF cat...

CMD cat -> args NULL, pipefd |, redirection infile
CMD wc -> args -l, pipefd |, redirection outfile
*/

/*
tokenization/lexer:
ls | wc -l > out.txt

ls => CMD, value = "ls"
| => PIPE, value = "|"
wc => CMD, value = "wc"
-l => ARGS, value = "-l"
> => TRUNC, value = ">"
out.txt => OUTFILE, value = "out.txt"

-------------------------
expansion:
cd ~
~ => /home/user
$USER => cde-sous
$HOME => /home/cde-sous

-------------------------
parsing:
creer la liste chainee de cmds avec leurs redirections et args

-------------------------
execution:
pipex complexe
*/

#endif