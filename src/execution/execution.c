/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:29:37 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/05 17:17:09 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	save_stds_and_execute_builtin(t_data *data, t_exec *exec_node)
{
	int	save_in;
	int	save_out;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	if (save_in == -1 || save_out == -1)
		return (print_error(4, "Dup", data), 1);
	if (!handle_files(data, exec_node))
	{
		close(save_in);
		close(save_out);
		return (1);
	}
	data->exit_code = execute_builtin(is_builtin(exec_node), data, exec_node,
			save_in, save_out);
	if (dup2(save_in, STDIN_FILENO) == -1 || dup2(save_out, STDOUT_FILENO) ==
		-1)
	{
		close(save_in);
		close(save_out);
		return (perror("Dup2"), 1);
	}
	close(save_in);
	close(save_out);
	return (data->exit_code);
}

void	execute(t_data *data)
{
	t_exec	*exec_node;

	exec_node = data->exec_list;
	if (is_builtin(exec_node) && !exec_node->next)
	{
		data->exit_code = save_stds_and_execute_builtin(data, exec_node);
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
			execute_child_process(exec_node, data);
		exec_node = exec_node->next;
	}
	close_all_pipefds(data);
	data->exit_code = wait_all_pids(data->exec_list);
	return ;
}
