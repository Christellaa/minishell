/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:17:58 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/30 09:30:03 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*name_here_doc(char *value, int *i)
{
	char	*name;
	char	*nb;

	nb = ft_itoa(*i); // + check fail malloc
	name = ft_strjoin(value, nb);
	if (!name)
	{
		// print_error?
		return (NULL);
	}
	(*i)++;
	return (name);
}
