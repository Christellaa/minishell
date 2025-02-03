/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/02/03 10:25:44 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		execute_builtin(int builtin, t_data *data, t_exec *exec_node);

void	check_builtin(t_data *data, t_exec *exec_node)
{
	int	builtin;
	int	save_in;
	int	save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	builtin = is_builtin(exec_node->arg_list->value);
	if (builtin)
	{
		if (!handle_redirs(data, exec_node))
		{
			cleanup(data, 1);
			exit(1);
		}
		dup2(save_in, STDIN_FILENO);
		dup2(save_out, STDOUT_FILENO);
		if (!execute_builtin(builtin, data, exec_node))
			exit(0);
		else
			exit(1);
	}
	close(save_in);
	close(save_out);
	return ;
}

int	execute_builtin(int builtin, t_data *data, t_exec *exec_node)
{
	// if (builtin == 1)
	// 	ft_echo(data, exec_node);
	/* else */ if (builtin == 2)
		ft_cd(data, exec_node);
	else if (builtin == 3)
		ft_pwd();
	else if (builtin == 4)
		ft_export(data, exec_node);
	else if (builtin == 5)
		ft_unset(data, exec_node);
	else if (builtin == 6)
		ft_env(data);
	else if (builtin == 7)
		ft_exit(data, exec_node);
	return (data->exit_code);
}
