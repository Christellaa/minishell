/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:58:40 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/09 19:20:01 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*trim_path(char *path_value);
int		get_path_len(char *path);

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
	return (trim_path(path_value));
}

char	*trim_path(char *path_value)
{
	char	*trimmed_path;
	char	*tmp_val;
	int		len;
	int		i;
	int		j;

	tmp_val = path_value;
	len = get_path_len(path_value);
	trimmed_path = malloc((len + 1) * sizeof(char));
	if (!trimmed_path)
		return (free(path_value), NULL);
	i = 0;
	j = 0;
	while (path_value[i])
	{
		if (tmp_val[i] != DOUBLE_QUOTE && tmp_val[i] != '\n')
			trimmed_path[j++] = path_value[i];
		i++;
	}
	trimmed_path[j] = '\0';
	free(path_value);
	return (trimmed_path);
}

int	get_path_len(char *path)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (path[i])
	{
		if (path[i] == DOUBLE_QUOTE || path[i] == '\n')
		{
			i++;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}
