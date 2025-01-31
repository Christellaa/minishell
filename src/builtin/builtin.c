/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cylini <cylini@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:49:37 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/31 21:52:32 by cylini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execute_builtin(int builtin, t_data *data, t_exec *exec_node);

void	check_builtin(t_data *data, t_exec *exec_node)
{
	int	builtin;

	builtin = is_builtin(exec_node->arg_list->value);
	if (builtin)
	{
		if (!handle_redirs(data, exec_node))
		{
			cleanup(data, 1);
			exit(1);
		}
		if (!execute_builtin(builtin, data, exec_node))
			exit(0);
		else
			exit(1);
	}
	return ;
}
int	execute_builtin(int builtin, t_data *data, t_exec *exec_node)
{
	(void)builtin;
	// if (builtin == 1)
	// 	ft_echo(data, exec_node);
	/* else if (builtin == 2); */
		ft_cd(data, exec_node);
	// else if (builtin == 3)
	// 	ft_pwd(data, exec_node);
	// else if (builtin == 4)
	// 	ft_export(data, exec_node);
	// else if (builtin == 5)
	// 	ft_unset(data, exec_node);
	// else if (builtin == 6)
	// 	ft_env(data, exec_node);
	/* else if (builtin == 7)*/
		// ft_exit(data, exec_node);
	return (data->exit_code);
}
