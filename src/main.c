/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:33:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 14:53:46 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (!data)
		return (print_error(6, NULL, NULL), 1);
	data = ft_memset(data, 0, sizeof(data));
	init_data(data);
	if (ac != 1)
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
		break ;
	}
	rl_clear_history();
	cleanup(data, 1);
}

/*
for export built-in:
- assignment key can only be alphanumeric + underscore
- if there's no '=' -> it will show in export() but not in env()
- export() reorders the env (uppercase then lowercase)
*/

// TODO:
// parsing protection
// create error messages (in .h) and their function
