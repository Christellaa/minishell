/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 15:56:32 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/06 13:28:36 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_data *data, t_exec *exec_node)
{
	t_env	*current_env;
	t_arg	*args;

	current_env = data->env_list;
	args = exec_node->arg_list->next;
	if (args)
	{
		ft_dprintf(STDERR_FILENO, "%s%s\n", args->value, FILE_ERR);
		data->exit_code = 127;
		return ;
	}
	while (current_env)
	{
		if (!(current_env->is_exported & IN_EXPORT)
			|| current_env->is_exported & IN_ENV)
			printf("%s\n", current_env->raw);
		current_env = current_env->next;
	}
}
