/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:33:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/14 12:14:14 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	test_it(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("token type: %d, value: %s\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

void	test_it_2(t_data *data)
{
	t_exec	*tmp;

	tmp = data->exec_list;
	while (tmp)
	{
		printf("cmd: %s\n", tmp->cmd);
		while (tmp->arg_list)
		{
			if (tmp->arg_list->value)
				printf("arg: %s\n", tmp->arg_list->value);
			tmp->arg_list = tmp->arg_list->next;
		}
		while (tmp->redirs)
		{
			if (tmp->redirs->value)
				printf("redir val: %s, type: %d\n", tmp->redirs->value,
					tmp->redirs->type);
			tmp->redirs = tmp->redirs->next;
		}
		printf("\n\nnext\n");
		tmp = tmp->next;
	}
}

void	process_input(t_data *data, char *input)
{
	if (lexer(data, input) == -1)
	{
		free(input);
		return ;
	}
	free(input);
	test_it(data); // testing lexing
	if (parser(data) >= 0)
	{
		printf("do expander + execution\n");
		expander(data);
	}
	else
		printf("cleanup for next loop\n");
	test_it(data); // testing parsing
	create_exec_list(data);
	test_it_2(data); // testing exec struct
}

void	init_data(t_data *data)
{
	data->token_list = NULL;
	data->exec_list = NULL;
	data->env_list = NULL;
	data->exit_code = 0;
	data->nb_cmd = 0;
	data->pids = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	data = malloc(sizeof(t_data));
	data = ft_memset(data, 0, sizeof(data));
	init_data(data);
	if (!data || ac != 1)
		return (1);
	create_env_list(data, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		process_input(data, input);
		cleanup(data, 0);
	}
	rl_clear_history();
	cleanup(data, 1);
}

/*
for export built-in:
- assignment key can only be alphanumeric + underscore
- if there's no '=' -> it will show in export() but not in env()
*/
