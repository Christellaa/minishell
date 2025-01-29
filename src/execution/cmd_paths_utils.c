/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:07:04 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/29 18:22:03 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			// if (!split_paths)
			// 	return (NULL);
			free(path_value);
			return (split_paths);
		}
		current_env = current_env->next;
	}
	/* get PATH:
	- aller dans /etc (=dossier)
	- trouver environment (=file)
	- trouver PATH dans environment file
	- copier pos ('=' + 2) jusqu'a len - 1 (pour ignorer les ")
	=> pour remplacer ce qui y a just en-dessous
	*/
	path_value = ft_strdup("/usr/local/sbin:/usr/local/bin:");
	if (!path_value)
		return (NULL);
	path_value = ft_strjoin(path_value, "/usr/sbin:/usr/bin:/sbin:/bin");
	// if (!path_value)
	// 	return (NULL);
	// check join failed
	split_paths = ft_split(path_value, ':'); // check split failed
	// if (!split_paths)
			// 	return (NULL);
	free(path_value);
	return (split_paths);
}

int	is_absolute_path(char *cmd)
{
	if (((ft_strncmp(cmd, "/", 1) == 0) || (ft_strncmp(cmd, "./", 2) == 0))
		&& access(cmd, F_OK | X_OK) == 0)
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
