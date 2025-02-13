/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:23 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/13 15:54:19 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin/builtin.h"
#include "execution.h"

void	execute_cmd(t_exec *exec_node, t_data *data);
char	*get_cmd_path(t_arg *arg_list, t_data *data);
void	free_paths(char **paths);
void	convert_and_execve(char *cmd_path, t_data *data, t_exec *exec_node);

int	execute_child_process(t_exec *exec_node, t_data *data)
{
	check_builtin(data, exec_node);
	if (!handle_redirs(data, exec_node))
	{
		close_all_pipefds(data);
		cleanup(data, 2);
		exit(1);
	}
	if (exec_node->arg_list)
		execute_cmd(exec_node, data);
	close_all_pipefds(data);
	cleanup(data, 2);
	exit(0);
}

void	execute_cmd(t_exec *exec_node, t_data *data)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(exec_node->arg_list, data);
	if (!cmd_path || !*cmd_path)
	{
		close_all_pipefds(data);
		cleanup(data, 2);
		if (cmd_path && !*cmd_path)
		{
			free(cmd_path);
			exit(126);
		}
		exit(127);
	}
	if (!close_all_pipefds(data))
	{
		free(cmd_path);
		cleanup(data, 2);
		exit(1);
	}
	convert_and_execve(cmd_path, data, exec_node);
}

char	*get_cmd_path(t_arg *arg_list, t_data *data)
{
	char	*final_path;
	char	**split_paths;
	char	*cmd;

	if (!arg_list)
		return (NULL);
	cmd = arg_list->value;
	split_paths = get_and_split_paths(data->env_list);
	if (!split_paths)
		return (print_error(9, arg_list->value, data), NULL);
	if (is_absolute_path(cmd))
		return (free_paths(split_paths), ft_strdup(cmd));
	final_path = get_relative_path(cmd, data, split_paths);
	if (!final_path)
		return (free_paths(split_paths), NULL);
	else if (*final_path)
		return (free_paths(split_paths), final_path);
	free(final_path);
	free_paths(split_paths);
	return (print_path_error(cmd, data));
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

void	convert_and_execve(char *cmd_path, t_data *data, t_exec *exec_node)
{
	char	**args;
	char	**env;

	args = convert_args_list_to_tab(exec_node->arg_list);
	env = convert_env_list_to_tab(data->env_list);
	if (!args || !env)
	{
		print_error(0, NULL, data);
		free(cmd_path);
		if (args)
			free(args);
		if (env)
			free(env);
		cleanup(data, 2);
		exit(1);
	}
	if (execve(cmd_path, args, env) == -1)
	{
		print_error(4, "Execve", data);
		free(cmd_path);
		free(args);
		free(env);
		cleanup(data, 2);
		exit(1);
	}
}
