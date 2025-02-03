/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:07:27 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/03 10:54:19 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_env_var(t_env *env_list, char *arg_value)
{
	t_env	*current_env;
	t_env	*prev;
	t_env	*next;

	current_env = env_list;
	prev = env_list;
	while (current_env)
	{
		if (ft_strcmp(arg_value, current_env->key) == 0)
		{
			next = current_env->next;
			if (prev == current_env)
				env_list = next;
			else
			{
				while (prev->next != current_env)
					prev = prev->next;
				prev->next = next;
			}
			return (free(current_env->raw), free(current_env->key),
				free(current_env->value));
		}
		current_env = current_env->next;
	}
}

void	ft_unset(t_data *data, t_exec *exec_node)
{
	t_arg	*args;

	args = exec_node->arg_list;
	args = args->next;
	if (!args)
		return ;
	while (args)
	{
		remove_env_var(data->env_list, args->value);
		args = args->next;
	}
}
