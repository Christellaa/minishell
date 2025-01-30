/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:50:47 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/30 17:23:47 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_file(t_files *current_file, int *here_doc_nb)
{
	int		fd;
	char	*name;

	if (current_file->type == INFILE)
		fd = open(current_file->value, O_RDONLY);
	else if (current_file->type == HEREDOC)
	{
		name = name_here_doc(current_file->value, here_doc_nb);
		if (!name)
			return (-2);
		fd = open(name, O_RDONLY);
		if (fd > 0)
			unlink(name);
	}
	else if (current_file->type == TRUNC)
		fd = open(current_file->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (current_file->type == APPEND)
		fd = open(current_file->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

int	dup2_and_close_current_file(t_files *current_file, t_data *data, int fd)
{
	if (current_file->type == INFILE || current_file->type == HEREDOC)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (print_error(4, "Dup2", data), 0);
		}
	}
	else if (current_file->type == TRUNC || current_file->type == APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (print_error(4, "Dup2", data), 0);
		}
	}
	if (close(fd) == -1)
		return (print_error(4, "Close", data), 0);
	return (1);
}

int	handle_files(t_data *data, t_exec *exec_node)
{
	t_files	*current_file;
	int		fd;
	int		here_doc_nb;

	current_file = exec_node->files;
	here_doc_nb = 0;
	while (current_file)
	{
		fd = open_file(current_file, &here_doc_nb);
		if (fd == -1 && access(current_file->value, F_OK) == 0)
			return (print_error(2, current_file->value, data), 0);
		else if (fd == -1)
			return (print_error(1, current_file->value, data), 0);
		else if (fd == -2)
			return (print_error(0, current_file->value, data), 0);
		if (!dup2_and_close_current_file(current_file, data, fd))
			return (0);
		current_file = current_file->next;
	}
	return (1);
}

int	handle_pipefd(t_data *data, t_exec *exec_node)
{
	if (data->exec_list != exec_node)
	{
		if (dup2(exec_node->pipefd[0], STDIN_FILENO) == -1)
			return (print_error(4, "Dup2", data), 0);
	}
	if (exec_node->next)
	{
		if (dup2(exec_node->pipefd[1], STDOUT_FILENO) == -1)
			return (print_error(4, "Dup2", data), 0);
	}
	return (1);
}

int	handle_redirs(t_data *data, t_exec *exec_node)
{
	if (!handle_pipefd(data, exec_node))
		return (0);
	if (!handle_files(data, exec_node))
		return (0);
	return (1);
}
