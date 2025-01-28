/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:29:37 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/28 16:11:13 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	create_pipes(t_data *data, t_exec *head_exec_list)
{
	t_exec	*current_node;

	current_node = head_exec_list;
	while (current_node)
	{
		if (pipe(current_node->pipefd) == -1)
			return (print_error(4, "Pipe", NULL, data), 0);
		current_node = current_node->next;
	}
	return (1);
}

char	**get_and_split_paths(t_env *env_list)
{
	char	*path_value;
	char	**split_paths;
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, "PATH") == 0)
		{
			path_value = ft_strdup(current_env->value);
			if (!path_value)
				return (NULL);
			split_paths = ft_split(path_value, ':');
			free(path_value);
			return (split_paths);
		}
		current_env = current_env->next;
	}
	path_value = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	if (!path_value)
		return (NULL);
	split_paths = ft_split(path_value, ':');
	free(path_value);
	return (split_paths);
}

int	is_absolute_path(char *cmd)
{
	if ((ft_strncmp(cmd, "/", 1) == 0) && access(cmd, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

char	*get_relative_path(char *cmd, t_data *data, char **split_paths)
{
	int		i;
	char	*path_with_slash;
	char	*final_path;

	i = -1;
	while (split_paths[++i])
	{
		path_with_slash = ft_strjoin(split_paths[i], "/");
		if (!path_with_slash)
			return (print_error(0, NULL, NULL, data), NULL);
		final_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (!final_path)
			return (print_error(0, NULL, NULL, data), NULL);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
	}
	return (ft_strdup(""));
}

char	*get_cmd_path(char *cmd, t_data *data)
{
	char	*final_path;
	char	**split_paths;
	int		i;

	split_paths = get_and_split_paths(data->env_list);
	if (!split_paths)
		return (print_error(0, NULL, NULL, data), NULL);
	if (is_absolute_path(cmd))
		return (free(split_paths), ft_strdup(cmd));
	final_path = get_relative_path(cmd, data, split_paths);
	if (!final_path)
		return (free(split_paths), NULL);
	else if (*final_path)
		return (free(split_paths), final_path);
	free(final_path);
	i = 0;
	while (split_paths[i])
		free(split_paths[i++]);
	free(split_paths);
	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, F_OK) == 0)
		return (print_error(10, cmd, NULL, data), ft_strdup(""));
	else if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
		data->exit_code = print_error(1, cmd, NULL, data);
	else
		data->exit_code = print_error(8, cmd, NULL, data);
	return (NULL);
}

t_exec	*get_prev_node(t_exec *list, t_exec *current)
{
	t_exec	*tmp_list;

	tmp_list = list;
	while (tmp_list && tmp_list->next != current)
		tmp_list = tmp_list->next;
	return (tmp_list);
}

void	write_in_heredoc(const char *delimiter, int fd)
{
	char	*line;
	int		line_nb;

	line_nb = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("\nwarning: here-document at line %d ", line_nb);
			printf("delimited by end of file (wanted '%s')\n", delimiter);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line_nb++;
	}
}

int	open_file(t_files *current_file)
{
	int	fd;

	if (current_file->type == INFILE)
		fd = open(current_file->value, O_RDONLY);
	else if (current_file->type == HEREDOC)
	{
		fd = open(".heredoc.tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			return (-1);
		write_in_heredoc(current_file->value, fd);
		if (close(fd) == -1)
			return (-2);
		fd = open(".heredoc.tmp", O_RDONLY);
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
			return (print_error(4, "Dup2", NULL, data), 0);
		}
	}
	else if (current_file->type == TRUNC || current_file->type == APPEND)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			close(fd);
			return (print_error(4, "Dup2", NULL, data), 0);
		}
	}
	if (close(fd) == -1)
	{
		close(fd);
		return (print_error(4, "Close", NULL, data), 0);
	}
	return (1);
}

int	handle_files(t_data *data, t_exec *exec_node)
{
	t_files	*current_file;
	int		fd;

	current_file = exec_node->files; // tmp ?
	while (current_file)
	{
		fd = open_file(current_file);
		if (fd == -1)
			return (print_error(4, "Open", NULL, data), 0);
		else if (fd == -2)
			return (print_error(4, "Close", NULL, data), 0);
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
			return (print_error(4, "Dup2", NULL, data), 0);
	}
	if (exec_node->next)
	{
		if (dup2(exec_node->pipefd[1], STDOUT_FILENO) == -1)
			return (print_error(4, "Dup2", NULL, data), 0);
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

char	**convert_args_list_to_tab(t_arg *arg_list)
{
	int		i;
	t_arg	*current_arg;
	char	**args_tab;

	i = 0;
	current_arg = arg_list;
	while (current_arg)
	{
		i++;
		current_arg = current_arg->next;
	}
	args_tab = malloc((i + 1) * sizeof(char *));
	if (!args_tab)
		return (NULL);
	i = 0;
	current_arg = arg_list;
	while (current_arg)
	{
		args_tab[i++] = current_arg->value;
		current_arg = current_arg->next;
	}
	args_tab[i] = NULL;
	return (args_tab);
}

char	**convert_env_list_to_tab(t_env *env_list)
{
	int		i;
	t_env	*current_env;
	char	**env_tab;

	i = 0;
	current_env = env_list;
	while (current_env)
	{
		i++;
		current_env = current_env->next;
	}
	env_tab = malloc((i + 1) * sizeof(char *));
	if (!env_tab)
		return (NULL);
	i = 0;
	current_env = env_list;
	while (current_env)
	{
		env_tab[i++] = current_env->raw;
		current_env = current_env->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
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
				return (print_error(4, "Close", NULL, data), 0);
		}
		if (current_node->pipefd[1] != -1)
		{
			if (close(current_node->pipefd[1]) == -1)
				return (print_error(4, "Close", NULL, data), 0);
		}
		current_node = current_node->next;
	}
	return (1);
}

int	execute_child_process(t_exec *exec_node, t_data *data)
{
	char	*cmd_path;
	char	**args;
	char	**env;

	if (!handle_redirs(data, exec_node))
		exit(data->exit_code);
	if (!close_all_pipefds(data))
		exit(data->exit_code);
	args = convert_args_list_to_tab(exec_node->arg_list);
	if (!args)
	{
		print_error(0, NULL, NULL, data);
		cleanup(data, 1);
		exit(data->exit_code);
	}
	env = convert_env_list_to_tab(data->env_list);
	if (!env)
	{
		free(args);
		print_error(0, NULL, NULL, data);
		cleanup(data, 1);
		exit(data->exit_code);
	}
	cmd_path = get_cmd_path(exec_node->arg_list->value, data);
	if (!cmd_path || !*cmd_path)
	{
		free(args);
		free(env);
		cleanup(data, 1);
		if (cmd_path && !*cmd_path)
		{
			free(cmd_path);
			exit(126);
		}
		exit(127);
	}
	if (execve(cmd_path, args, env) == -1)
	{
		data->exit_code = print_error(4, "Execve", NULL, data);
		free(cmd_path);
		free(args);
		free(env);
		cleanup(data, 1);
		exit(data->exit_code);
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
		// if (pid == -1 && errno == ECHILD)
		// 	break ;
		// else if (pid == -1 && errno == EINTR)
		// 	continue ;
		/* else  */ if (pid == last_cmd->pid)
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
	// if (is_builtin(exec_node->arg_list->value) && !exec_node->next
	// 	&& handle_files(data, exec_node))
	// 	printf("builtin, execute ds main process");
	if (!create_pipes(data, exec_node))
		return ;
	while (exec_node)
	{
		handle_child_signals();
		exec_node->pid = fork();
		if (exec_node->pid == -1)
		{
			print_error(4, "Fork", NULL, data);
			return ;
		}
		if (!exec_node->pid)
		{
			data->exit_code = execute_child_process(exec_node, data);
		}
		exec_node = exec_node->next;
	}
	data->exit_code = wait_all_pids(data->exec_list);
	close_all_pipefds(data);
	return ;
}

/// AAA