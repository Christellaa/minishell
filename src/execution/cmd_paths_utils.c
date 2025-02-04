/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_paths_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:07:04 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/04 14:56:37 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_path_from_its_file(void)
{
	char		*path_value;
	int			fd;
	struct stat	file_stat;
	size_t		file_size;
	ssize_t		bytes_read;

	fd = open("/etc/environment", O_RDONLY);
	if (fd == -1)
		return (perror("/etc/environment"), NULL);
	if (fstat(fd, &file_stat) < 0)
		return (close(fd), perror("Error getting file size"), NULL);
	file_size = file_stat.st_size;
	if (file_size == 0)
		return (close(fd), NULL);
	path_value = malloc(file_size + 1);
	if (!path_value)
		return (close(fd), perror("Malloc error"), NULL);
	bytes_read = read(fd, path_value, file_size);
	close(fd);
	if (bytes_read < 0)
		return (free(path_value), perror("Error reading file"), NULL);
	path_value[bytes_read] = '\0';
	return (path_value);
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
	path_value = get_path_from_its_file();
	if (!path_value)
		return (NULL);
	split_paths = ft_split(path_value, ':');
	if (!split_paths)
		return (NULL);
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
			return (print_error(0, NULL, data), NULL);
		final_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (!final_path)
			return (print_error(0, NULL, data), NULL);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
	}
	return (ft_strdup(""));
}
