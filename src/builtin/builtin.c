/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:55:50 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/10 12:35:42 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/execution.h"
#include "builtin.h"

int		execute_builtin(int builtin, t_data *data, t_exec *exec_node);

int	is_builtin(t_exec *exec_node)
{
	char	*cmd;

	if (!exec_node->arg_list)
		return (0);
	cmd = exec_node->arg_list->value;
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd, "export") == 0)
		return (4);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd, "env") == 0)
		return (6);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

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
		builtin = execute_builtin(builtin, data, exec_node);
		close_all_pipefds(data);
		cleanup(data, 2);
		if (!builtin)
			exit(0);
		else
			exit(data->exit_code);
	}
	return ;
}

int	execute_builtin(int builtin, t_data *data, t_exec *exec_node)
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
		ft_exit(data, exec_node, -1, -1);
	return (data->exit_code);
}
