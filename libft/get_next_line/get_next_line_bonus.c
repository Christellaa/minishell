/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:59:11 by cde-sous          #+#    #+#             */
/*   Updated: 2024/10/14 21:09:53 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_until_newline_or_eof(int fd, char **buffer)
{
	char	*current_buffer;
	ssize_t	read_bytes;
	char	*tmp;

	current_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!current_buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, current_buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(current_buffer);
			return (NULL);
		}
		current_buffer[read_bytes] = '\0';
		tmp = ft_strjoin_free_s1(*buffer, current_buffer);
		*buffer = tmp;
		if (ft_strchr(current_buffer, '\n'))
			break ;
	}
	free(current_buffer);
	return (*buffer);
}

char	*extract_line(char *buffer)
{
	size_t	index;
	char	*cut_line;

	index = 0;
	if (!buffer[index])
		return (NULL);
	while (buffer[index] && buffer[index] != '\n')
		index++;
	cut_line = ft_calloc(index + 2, sizeof(char));
	if (!cut_line)
		return (NULL);
	index = 0;
	while (buffer[index] && buffer[index] != '\n')
	{
		cut_line[index] = buffer[index];
		index++;
	}
	cut_line[index] = buffer[index];
	cut_line[index + 1] = '\0';
	return (cut_line);
}

char	*keep_rest(char *buffer)
{
	size_t	newline_index;
	size_t	i;
	char	*rest;

	newline_index = 0;
	while (buffer[newline_index] && buffer[newline_index] != '\n')
		newline_index++;
	newline_index++;
	rest = ft_calloc(ft_strlen(buffer) - newline_index + 1, sizeof(char));
	if (!rest)
	{
		free(buffer);
		return (NULL);
	}
	i = -1;
	while (buffer[newline_index + ++i])
		rest[i] = buffer[newline_index + i];
	free(buffer);
	if (!*rest)
	{
		free(rest);
		rest = NULL;
	}
	return (rest);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffers[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffers[fd]);
		buffers[fd] = NULL;
		return (NULL);
	}
	if (!buffers[fd])
		buffers[fd] = ft_calloc(1, sizeof(char));
	buffers[fd] = read_until_newline_or_eof(fd, &buffers[fd]);
	if (!buffers[fd])
		return (NULL);
	line = extract_line(buffers[fd]);
	buffers[fd] = keep_rest(buffers[fd]);
	return (line);
}
