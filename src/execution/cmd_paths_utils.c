/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:07:04 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/09 18:59:36 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

t_env	*find_path_var(t_env *env_list);
char	*get_path_from_its_file(void);

char	**get_and_split_paths(t_env *env_list)
{
	char	*path_value;
	char	**split_paths;
	t_env	*current_env;

	current_env = find_path_var(env_list);
	if (current_env)
	{
		path_value = ft_strdup(current_env->value);
		if (!path_value)
			return (NULL);
		split_paths = ft_split(path_value, ':');
		if (!split_paths)
			return (NULL);
		free(path_value);
		return (split_paths);
	}
	return (NULL);
}

t_env	*find_path_var(t_env *env_list)
{
	t_env	*current_env;

	current_env = env_list;
	while (current_env)
	{
		if (ft_strcmp(current_env->key, "PATH") == 0)
			return (current_env);
		current_env = current_env->next;
	}
	return (NULL);
}

int	is_absolute_path(char *cmd)
{
	struct stat	path_stat;

	if (((ft_strncmp(cmd, "/", 1) == 0) || (ft_strncmp(cmd, "./", 2) == 0))
		&& access(cmd, F_OK | X_OK) == 0)
	{
		if (stat(cmd, &path_stat) != -1 && S_ISDIR(path_stat.st_mode))
			return (0);
		return (1);
	}
	return (0);
}

char	*get_relative_path(char *cmd, t_data *data, char **split_paths)
{
	int			i;
	char		*path_with_slash;
	char		*final_path;
	struct stat	path_stat;

	i = -1;
	while (split_paths[++i])
	{
		path_with_slash = ft_strjoin(split_paths[i], "/");
		if (!path_with_slash)
			return (print_error(0, NULL, data), NULL);
		final_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (!final_path)
			return (print_error(0, NULL, data), NULL);
		if (access(final_path, F_OK | X_OK) == 0 && (stat(cmd, &path_stat) == -1
				|| !S_ISDIR(path_stat.st_mode)))
			return (final_path);
		free(final_path);
	}
	return (ft_strdup(""));
}
