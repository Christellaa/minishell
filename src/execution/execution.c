/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:29:37 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/30 17:24:37 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
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

int	create_pipes(t_data *data, t_exec *head_exec_list)
{
	t_exec	*current_node;
	int		pipes[2];

	current_node = head_exec_list;
	while (current_node)
	{
		if (!current_node->next)
			return (1);
		if (pipe(pipes) == -1)
			return (print_error(4, "Pipe", data), 0);
		current_node->next->pipefd[0] = pipes[0];
		current_node->pipefd[1] = pipes[1];
		current_node = current_node->next;
	}
	return (1);
}

int	close_all_pipefds(t_data *data)
{
	t_exec	*current_node;

	current_node = data->exec_list;
	while (current_node)
	{
		if (current_node->pipefd[0] != -1)
		{
			if (close(current_node->pipefd[0]) == -1)
				return (print_error(4, "Close", data), 0);
		}
		if (current_node->pipefd[1] != -1)
		{
			if (close(current_node->pipefd[1]) == -1)
				return (print_error(4, "Close", data), 0);
		}
		current_node = current_node->next;
	}
	return (1);
}

int	wait_all_pids(t_exec *head_exec_list)
{
	int		status_info;
	int		exit_code;
	t_exec	*last_cmd;
	pid_t	pid;

	last_cmd = head_exec_list;
	exit_code = 0;
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	while (errno != ECHILD)
	{
		pid = waitpid(-1, &status_info, 0);
		if (pid == last_cmd->pid)
		{
			if (WIFEXITED(status_info))
				exit_code = WEXITSTATUS(status_info);
			else if (WIFSIGNALED(status_info))
				exit_code = WTERMSIG(status_info);
		}
	}
	return (exit_code);
}

void	execute(t_data *data)
{
	t_exec	*exec_node;

	exec_node = data->exec_list;
	if (is_builtin(exec_node->arg_list->value) && !exec_node->next
		&& handle_files(data, exec_node))
	{
		execute_builtin(is_builtin(exec_node->arg_list->value), data,
			exec_node);
		return ;
	}
	if (!create_pipes(data, exec_node))
		return ;
	while (exec_node)
	{
		handle_child_signals();
		exec_node->pid = fork();
		if (exec_node->pid == -1)
		{
			print_error(4, "Fork", data);
			return ;
		}
		if (!exec_node->pid)
			data->exit_code = execute_child_process(exec_node, data);
		exec_node = exec_node->next;
	}
	close_all_pipefds(data);
	data->exit_code = wait_all_pids(data->exec_list);
	return ;
}

// ls|<<u <<r grep b => seulement le resultat de r s'affiche (OK)
// ls|<<u grep a |<<r grep b => seulemet le res de r s'affiche (OK)
