/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 21:12:25 by cde-sous          #+#    #+#             */
/*   Updated: 2025/02/07 22:09:49 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_tools.h"

char	*read_pid_file(int fd, char *buffer, size_t buffer_size, t_data *data);
char	*get_pid(char *buffer, t_data *data);
char	*trim_pid(char *buffer);

char	*handle_pid(t_data *data)
{
	int		fd;
	int		i;
	char	buffer[256];
	char	*pid;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (print_error(0, NULL, data), NULL);
	i = 0;
	while (i < 256)
		buffer[i++] = '\0';
	pid = read_pid_file(fd, buffer, sizeof(buffer), data);
	return (pid);
}

char	*read_pid_file(int fd, char *buffer, size_t buffer_size, t_data *data)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, buffer_size - 1);
	close(fd);
	if (bytes_read < 0)
		return (print_error(4, "Read", data), NULL);
	buffer[bytes_read] = '\0';
	return (get_pid(buffer, data));
}

char	*get_pid(char *buffer, t_data *data)
{
	int		i;
	int		space_count;
	char	*trimmed_pid;

	i = 0;
	space_count = 0;
	while (buffer[i])
	{
		if (buffer[i] == ' ')
			space_count++;
		if (space_count == 3)
			break ;
		i++;
	}
	trimmed_pid = trim_pid(&buffer[i] + 1);
	if (!trimmed_pid)
		print_error(0, NULL, data);
	return (trimmed_pid);
}

char	*trim_pid(char *buffer)
{
	char	*start;
	char	*end;
	int		len;
	char	*pid;
	int		i;

	start = buffer;
	end = start;
	while (*end && *end != ' ')
		end++;
	len = end - start;
	pid = malloc((len + 1) * sizeof(char));
	if (!pid)
		return (NULL);
	i = -1;
	while (++i < len)
		pid[i] = start[i];
	pid[len] = '\0';
	return (pid);
}
