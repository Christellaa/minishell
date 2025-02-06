/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/06 15:30:09 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"
#include "builtin.h"

int		execute_builtin(int builtin, t_data *data, t_exec *exec_node,
			int save_in, int save_out);

void	check_builtin(t_data *data, t_exec *exec_node)
{
	int	builtin;

	builtin = is_builtin(exec_node);
	if (builtin)
	{
		if (!handle_redirs(data, exec_node))
		{
			cleanup(data, 2);
			exit(1);
		}
		builtin = execute_builtin(builtin, data, exec_node, -1, -1);
		close_all_pipefds(data);
		cleanup(data, 2);
		if (!builtin)
			exit(0);
		else
			exit(1);
	}
	return ;
}

int	execute_builtin(int builtin, t_data *data, t_exec *exec_node, int save_in,
		int save_out)
{
	if (builtin == 1)
		ft_echo(exec_node);
	else if (builtin == 2)
		ft_cd(data, exec_node);
	else if (builtin == 3)
		ft_pwd(data, exec_node);
	else if (builtin == 4)
		ft_export(data, exec_node);
	else if (builtin == 5)
		ft_unset(data, exec_node);
	else if (builtin == 6)
		ft_env(data, exec_node);
	else if (builtin == 7)
		ft_exit(data, exec_node, save_in, save_out);
	return (data->exit_code);
}
