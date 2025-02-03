/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:01:56 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/03 17:43:07 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token *token);
void	free_exec(t_exec *exec);
void	free_env(t_env *pair);

void	cleanup(t_data *data, int type)
{
	if (data)
	{
		if (data->token_list)
			free_tokens(data->token_list);
		data->token_list = NULL;
		if (data->exec_list)
			free_exec(data->exec_list);
		data->exec_list = NULL;
		if (type == 1) // for parent process
		{
			handle_exit_shlvl();
			if (data->env_list)
				free_env(data->env_list);
			free(data);
			rl_clear_history();
		}
		else if (type == 2) // for child process
		{
			if (data->env_list)
				free_env(data->env_list);
			free(data);
			rl_clear_history();
		}
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_exec(t_exec *exec)
{
	t_exec	*tmp;
	t_arg	*arg;
	t_files	*file;

	while (exec)
	{
		tmp = exec;
		exec = exec->next;
		while (tmp->arg_list)
		{
			arg = tmp->arg_list;
			tmp->arg_list = tmp->arg_list->next;
			free(arg);
		}
		while (tmp->files)
		{
			file = tmp->files;
			tmp->files = tmp->files->next;
			free(file);
		}
		free(tmp);
	}
}

void	free_env(t_env *pair)
{
	t_env	*tmp;

	while (pair)
	{
		tmp = pair;
		pair = pair->next;
		free(tmp->raw);
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}
