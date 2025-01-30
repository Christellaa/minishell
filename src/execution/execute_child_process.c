/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:45:23 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/30 14:34:12 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
char	*get_cmd_path(char *cmd, t_data *data)
{
	char	*final_path;
	char	**split_paths;
	int		i;

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
	if (ft_strncmp(cmd, "./", 2) == 0 && access(cmd, F_OK) == 0)
		return (print_error(7, cmd, data), ft_strdup(""));
	else if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0)
		print_error(1, cmd, data);
	else
		print_error(8, cmd, data);
	return (NULL);
}

int	execute_child_process(t_exec *exec_node, t_data *data)
{
	char	*cmd_path;
	char	**args;
	char	**env;

	check_builtin(data, exec_node);
	cmd_path = get_cmd_path(exec_node->arg_list->value, data);
	if (!cmd_path || !*cmd_path)
	{
		cleanup(data, 1);
		if (cmd_path && !*cmd_path)
		{
			free(cmd_path);
			exit(126);
		}
		exit(127);
	}
	if (!handle_redirs(data, exec_node) || !close_all_pipefds(data))
	{
		free(cmd_path);
		cleanup(data, 1);
		exit(1);
	}
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
		cleanup(data, 1);
		exit(1);
	}
	if (execve(cmd_path, args, env) == -1)
	{
		print_error(4, "Execve", data);
		free(cmd_path);
		free(args);
		free(env);
		cleanup(data, 1);
		exit(1);
	}
	return (1);
}
