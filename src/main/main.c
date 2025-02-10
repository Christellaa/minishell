/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:33:43 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/10 14:14:46 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../env/env.h"
#include "../execution/execution.h"
#include "../parsing/parsing.h"

t_data	*init_data(void);
void	process_input(t_data *data, char *input);
// void	test_parsing(t_data *data);
// void	test_exec(t_data *data);

int		g_signal;

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;

	(void)av;
	g_signal = 0;
	if (!isatty(STDOUT_FILENO))
		return (1);
	data = init_data();
	if (!data)
		return (print_error(0, NULL, data), cleanup(data, 1), 1);
	if (ac != 1)
		return (print_error(3, NULL, data), cleanup(data, 1), 1);
	if (!get_env_list(data, envp))
		return (cleanup(data, 1), 1);
	while (1)
	{
		handle_parent_signals();
		input = readline("minishell$ ");
		if (!input)
			return (printf("exit\n"), free(input), cleanup(data, 1), 0);
		add_history(input);
		process_input(data, input);
		cleanup(data, 0);
	}
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data = ft_memset(data, 0, sizeof(data));
	data->token_list = NULL;
	data->exec_list = NULL;
	data->env_list = NULL;
	data->exit_code = 0;
	return (data);
}

void	process_input(t_data *data, char *input)
{
	if (!parse_input(data, input))
		return ;
	if (!create_exec_list(data))
		return ;
	if (!handle_here_doc(data, data->exec_list))
		return ;
	execute(data);
}
/*
void	test_parsing(t_data *data)
{
	t_token	*tmp;

	tmp = data->token_list;
	while (tmp)
	{
		printf("token type: %d, value: [%s]\n", tmp->type, tmp->value);
		tmp = tmp->next;
	}
}

void	test_exec(t_data *data)
{
	t_exec	*tmp;
	t_arg	*arg;
	t_files	*file;

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
		file = tmp->files;
		while (file)
		{
			if (file->value)
				printf("file val: [%s], type: %d\n", file->value, file->type);
			file = file->next;
		}
		if (tmp->next)
			printf("\n\nnext\n");
		tmp = tmp->next;
	}
}
*/
