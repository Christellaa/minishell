/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:17:58 by carzhang          #+#    #+#             */
/*   Updated: 2025/02/06 13:52:43 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		write_mode_here_doc(t_files *file, int *i, t_data *data);
char	*name_here_doc(char *value, int *i);
void	write_in_heredoc(const char *delimiter, int fd);

int	handle_here_doc(t_data *data, t_exec *node)
{
	t_files	*file;
	int		i;
	t_exec	*node_tmp;

	node_tmp = node;
	while (node_tmp)
	{
		i = 0;
		file = node_tmp->files;
		while (file)
		{
			if (!write_mode_here_doc(file, &i, data))
				return (0);
			file = file->next;
		}
		node_tmp = node_tmp->next;
	}
	return (1);
}

int	write_mode_here_doc(t_files *file, int *i, t_data *data)
{
	char	*name;
	int		fd;

	if (file->type == HEREDOC)
	{
		name = name_here_doc(file->value, i);
		if (!name)
			return (print_error(0, NULL, data), 0);
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			if (fd == -1)
				return (perror(file->value), 0);
		write_in_heredoc(file->value, fd);
		if (close(fd) == -1)
		{
			unlink(name);
			return (print_error(4, "Close", data), 0);
		}
	}
	return (1);
}

char	*name_here_doc(char *value, int *i)
{
	char	*name;
	char	*nb;

	nb = ft_itoa(*i);
	if (!nb)
		return (NULL);
	name = ft_strjoin(value, nb);
	if (!name)
	{
		free(nb);
		return (NULL);
	}
	(*i)++;
	return (name);
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
