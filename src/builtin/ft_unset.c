/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:07:27 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 20:37:18 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		is_option(char *arg_value, t_data *data);
void	remove_env_var(t_env **env_list, char *arg_value);

void	ft_unset(t_data *data, t_exec *exec_node)
{
	t_arg	*args;

	args = exec_node->arg_list->next;
	if (!args)
		return ;
	while (args)
	{
		if (is_option(args->value, data))
			return ;
		remove_env_var(&data->env_list, args->value);
		args = args->next;
	}
}

int	is_option(char *arg_value, t_data *data)
{
	if (arg_value[0] == '-')
	{
		ft_dprintf(STDERR_FILENO, "unset: %s: invalid option\n", arg_value);
		data->exit_code = 2;
		return (1);
	}
	return (0);
}

void	remove_env_var(t_env **env_list, char *arg_value)
{
	t_env	*current_env;
	t_env	*prev;
	t_env	*next;

	current_env = *env_list;
	prev = NULL;
	while (current_env)
	{
		if (ft_strcmp(arg_value, current_env->key) == 0)
		{
			next = current_env->next;
			if (prev == NULL)
				*env_list = next;
			else
				prev->next = next;
			return (free(current_env->raw), free(current_env->key),
				free(current_env->value), free(current_env));
		}
		prev = current_env;
		current_env = current_env->next;
	}
}
