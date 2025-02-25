/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:29:37 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/10 14:06:48 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin/builtin.h"
#include "execution.h"

void	save_stds_and_execute_builtin(t_data *data, t_exec *exec_node);
int		create_pipes(t_data *data, t_exec *head_exec_list);
int		wait_all_pids(t_exec *head_exec_list);

void	execute(t_data *data)
{
	t_exec	*exec_node;

	exec_node = data->exec_list;
	if (is_builtin(exec_node) && !exec_node->next)
		return (save_stds_and_execute_builtin(data, exec_node));
	if (!create_pipes(data, exec_node))
		return ;
	while (exec_node)
	{
		handle_child_signals();
		exec_node->pid = fork();
		if (exec_node->pid == -1)
			return (print_error(4, "Fork", data));
		if (!exec_node->pid)
			execute_child_process(exec_node, data);
		exec_node = exec_node->next;
	}
	close_all_pipefds(data);
	data->exit_code = wait_all_pids(data->exec_list);
}

void	save_stds_and_execute_builtin(t_data *data, t_exec *exec_node)
{
	int	std_in;
	int	std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	if (std_in == -1 || std_out == -1)
		return (print_error(4, "Dup", data));
	if (!handle_files(data, exec_node))
	{
		data->exit_code = 1;
		return (dup_and_close_files(std_in, std_out, 0, data));
	}
	if (is_builtin(exec_node) == 7)
	{
		ft_exit(data, exec_node, std_in, std_out);
		return (dup_and_close_files(std_in, std_out, 1, data));
	}
	execute_builtin(is_builtin(exec_node), data, exec_node);
	dup_and_close_files(std_in, std_out, 1, data);
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
			{
				current_node->pipefd[0] = -1;
				return (print_error(4, "Close", data), 0);
			}
		}
		if (current_node->pipefd[1] != -1)
		{
			if (close(current_node->pipefd[1]) == -1)
			{
				current_node->pipefd[1] = -1;
				return (print_error(4, "Close", data), 0);
			}
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
