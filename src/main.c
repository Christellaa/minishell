/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:33:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/23 11:06:43 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal;

void	test_it(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("token type: %d, value: [%s]\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

void	test_it_2(t_data *data)
{
	t_exec		*tmp;
	t_arg		*arg;
	t_redirs	*redir;

	tmp = data->exec_list;
	while (tmp)
	{
		arg = tmp->arg_list;
		while (arg)
		{
			if (arg->value)
				printf("arg: [%s]\n", arg->value);
			arg = arg->next;
		}
		redir = tmp->redirs;
		while (redir)
		{
			if (redir->value)
				printf("redir val: [%s], type: %d\n", redir->value,
					redir->type);
			redir = redir->next;
		}
		printf("\n\nnext\n");
		tmp = tmp->next;
	}
}

void	process_input(t_data *data, char *input)
{
	if (!parser(data, input))
		return ;
	test_it(data); // testing parsing
	if (!create_exec_list(data))
		return ;
	test_it_2(data); // testing exec struct
						// if (!execute(data))
						// 	return ;
}

void	init_data(t_data *data)
{
	data->token_list = NULL;
	data->exec_list = NULL;
	data->env_list = NULL;
	data->exit_code = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	g_signal = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (print_error(6, NULL, NULL), 1);
	data = ft_memset(data, 0, sizeof(data));
	init_data(data);
	if (ac != 1)
		return (print_error(7, NULL, NULL), 1);
	if (!create_env_list(data, envp))
		return (cleanup(data, 1), 1);
	handle_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (printf("exit\n"), free(input), cleanup(data, 1), 0);
		add_history(input);
		process_input(data, input);
		cleanup(data, 0);
	}
}

/*
TODO:
- augmenter shlvl a chaque ouverture de ./minishell
=> implement a way to persist the env (save to a file?)
- _ = dernier arg d'un node solo (cmd incluse)
*/

/*
QUESTIONS:
- what's the FD_MAX allowed?
- what's the SHLVL_MAX allowed?
*/

/*
for export built-in:
- assignment key can only be alphanumeric + underscore
- if there's no '=' -> it will show in export() but not in env()
- if show_in_env = 2 -> it will show in env() but not in export()
- export() reorders the env (uppercase then lowercase)
	+ show value inside double quotes

for signals:
inside child processes:
-> ctrl+d does nothing
-> ctrl+c stop process => 130
-> ctrl+\ stop process (core dumped) => 131

for execution:
-> signals don't copy to child process
-> STDIN and STDOUT must be dup before dup2 when exec is in main process,
	then dup2 modified with original ones before closing modified ones
eg:
save_out = dup(STDOUT);
fd = open(WRITE);
dup2(fd, STDOUT);
exec
dup2(save_out, STDOUT);
close(save_out);

si plusieurs nodes ou pas builtin:
1. pipe(pipefd) pour chaque node sauf le dernier où pipefd[0] = pipefd[1] = -1
2. loop through nodes
- fork
- handle redirs:
-- if there are redirs:
--- loop through redirs
----open file
----- if heredoc -> open WRITE, nommer, ecrire dedans, close et open READ
---- dup2 file with stdin or stdout
---- close file
-- if it's not the last node:
--- if there are no redirs CHEVRON_GAUCHE && there's a prev node:
	dup2 prevfdout with STDIN
--- if there are no redirs CHEVRON_DROITE
	&& there's a next node: dup2 pipefd[1] with STDOUT
--- close pipefd[0], pipefd[1] and prevfdout
- handle path
- execve
3. waitpid
*/
// ls > a > b > c | wc - l
