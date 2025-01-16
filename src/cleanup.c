/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:01:56 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/16 16:08:59 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	t_exec		*tmp;
	t_arg		*arg;
	t_redirs	*redir;

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
		while (tmp->redirs)
		{
			redir = tmp->redirs;
			tmp->redirs = tmp->redirs->next;
			free(redir);
		}
		free(tmp);
	}
}

int	cleanup(t_data *data, int type)
{
	if (data)
	{
		if (type == 1) // cleanup at the end
		{
			if (data->token_list)
				free_tokens(data->token_list);
			data->token_list = NULL;
			if (data->exec_list)
				free_exec(data->exec_list);
			data->exec_list = NULL;
			if (data->env_list)
				free_env(data->env_list);
			free(data);
		}
		if (type == 0) // cleanup at each loop
		{
			if (data->token_list)
				free_tokens(data->token_list);
			data->token_list = NULL;
			if (data->exec_list)
				free_exec(data->exec_list);
			data->exec_list = NULL;
		}
	}
	return (0);
}
