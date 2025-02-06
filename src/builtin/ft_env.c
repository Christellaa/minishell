/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:56:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 18:33:32 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		check_args(t_arg *arg, t_data *data, t_exec *exec_node);

void	ft_env(t_data *data, t_exec *exec_node)
{
	t_env	*current_env;
	t_arg	*args;
	int		err_code;

	current_env = data->env_list;
	args = exec_node->arg_list->next;
	err_code = check_args(args, data, exec_node);
	if (err_code == 0)
		return ;
	while (current_env)
	{
		if (!(current_env->is_exported & IN_EXPORT)
			|| current_env->is_exported & IN_ENV)
			printf("%s\n", current_env->raw);
		current_env = current_env->next;
	}
}

int	check_args(t_arg *arg, t_data *data, t_exec *exec_node)
{
	while (arg)
	{
		if (ft_strcmp(arg->value, "env") != 0)
		{
			if (arg->value[0] == '-')
			{
				ft_dprintf(STDERR_FILENO, "env: %s: invalid option\n",
					arg->value);
				data->exit_code = 2;
			}
			else
			{
				ft_dprintf(STDERR_FILENO, "%s: '%s'%s\n",
					exec_node->arg_list->value, arg->value, FILE_ERR);
				data->exit_code = 127;
			}
			return (0);
		}
		arg = arg->next;
	}
	return (1);
}
