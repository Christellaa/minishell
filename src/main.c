/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:33:43 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/09 14:19:56 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_data *data)
{
	data->token_list = NULL;
	data->cmd_list = NULL;
	data->env_list = NULL;
	data->exit_code = 0;
	data->nb_cmd = 0;
	data->pids = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_data	*data;
	t_token	*tmp;

	(void)av;
	data = malloc(sizeof(t_data));
	data = ft_memset(data, 0, sizeof(data));
	init_data(data);
	if (!data || ac != 1)
		return (1);
	get_env_list(data, envp);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		lexer(data, input);
		free(input);
		// test it!
		tmp = data->token_list;
		while (tmp)
		{
			printf("token type: %d, value: %s\n", tmp->type, tmp->value);
			tmp = tmp->next;
		}
		cleanup(data, 0);
	}
	rl_clear_history();
	cleanup(data, 1);
}
