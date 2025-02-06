/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:23 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/06 17:52:48 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtin/builtin.h"
#include "execution.h"

char	*get_cmd_path(t_arg *arg_list, t_data *data);
char	*no_such_file_or_directory(char *cmd, t_data *data);
char	**convert_args_list_to_tab(t_arg *arg_list);
char	**convert_env_list_to_tab(t_env *env_list);
void	convert_and_check(char *cmd_path, t_data *data, t_exec *exec_node);

int	execute_child_process(t_exec *exec_node, t_data *data)
{
	char	*cmd_path;

	check_builtin(data, exec_node);
	if (!handle_redirs(data, exec_node))
	{
		close_all_pipefds(data);
		cleanup(data, 2);
		exit(1);
	}
	cmd_path = get_cmd_path(exec_node->arg_list, data);
	if (!cmd_path || !*cmd_path || !close_all_pipefds(data))
	{
		cleanup(data, 2);
		if (cmd_path && !*cmd_path)
		{
			free(cmd_path);
			exit(126);
		}
		exit(127);
	}
	convert_and_check(cmd_path, data, exec_node);
	return (1);
}

char	*get_cmd_path(t_arg *arg_list, t_data *data)
{
	char	*final_path;
	char	**split_paths;
	int		i;
	char	*cmd;

	if (!arg_list)
		return (NULL);
	cmd = arg_list->value;
	split_paths = get_and_split_paths(data->env_list);
	if (!split_paths)
		return (print_error(0, NULL, data), NULL);
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
	return (no_such_file_or_directory(cmd, data));
}

char	*no_such_file_or_directory(char *cmd, t_data *data)
{
	struct stat	path_stat;

	if (stat(cmd, &path_stat) != -1 && S_ISDIR(path_stat.st_mode))
		return (ft_dprintf(STDERR_FILENO, "%s: is a directory\n", cmd),
			ft_strdup(""));
	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, F_OK) == 0)
		return (print_error(7, cmd, data), ft_strdup(""));
	else if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
		print_error(9, cmd, data);
	else
		print_error(8, cmd, data);
	return (NULL);
}

void	convert_and_check(char *cmd_path, t_data *data, t_exec *exec_node)
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
