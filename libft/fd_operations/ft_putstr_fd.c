/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:56:26 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:37:10 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Outputs s to fd
** Returns nothing
*/

#include "../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}
/* 
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
void	test_putstr_fd_leading_trailing_whitespace()
{
	int		fd;
	char	*str = "   Hello, World!   ";
	char	buf[30];

	fd = open("test1.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	assert(fd!= -1);

	ft_putstr_fd(str, fd);
	close(fd);

	fd = open("test1.txt", O_RDONLY);
	assert(fd!= -1);

	read(fd, buf, strlen(str));
	close(fd);

	buf[strlen(str)] = '\0';
	assert(strcmp(buf, str) == 0);
}void	test_putstr_fd_empty_string()
{
	int		fd;
	char	*str = "";
	char	buf[1];

	fd = open("test2.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	assert(fd!= -1);

	ft_putstr_fd(str, fd);
	close(fd);

	fd = open("test2.txt", O_RDONLY);
	assert(fd!= -1);

	read(fd, buf, 0);
	close(fd);

	assert(buf[0] == '\0');
}void	test_putstr_fd_only_whitespace()
{
	int		fd;
	char	*str = "   \t\n   ";
	char	buf[10];

	fd = open("test3.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	assert(fd!= -1);

	ft_putstr_fd(str, fd);
	close(fd);

	fd = open("test3.txt", O_RDONLY);
	assert(fd!= -1);

	read(fd, buf, strlen(str));
	close(fd);

	buf[strlen(str)] = '\0';
	assert(strcmp(buf, str) == 0);
}void	test_putstr_fd_long_string()
{
	int		fd;
	char	str[10000];
	char	buf[10000];
	int		i;

	for (i = 0; i < 9999; i++)
		str[i] = 'a';
	str[9999] = '\0';

	fd = open("test4.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	assert(fd!= -1);

	ft_putstr_fd(str, fd);
	close(fd);

	fd = open("test4.txt", O_RDONLY);
	assert(fd!= -1);

	read(fd, buf, 9999);
	close(fd);

	buf[9999] = '\0';
	assert(strcmp(buf, str) == 0);
}void	test_putstr_fd_non_printable()
{
	int		fd;
	char	*str = "Hello,\n\tWorld!\0";
	char	buf[20];

	fd = open("test5.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	assert(fd!= -1);

	ft_putstr_fd(str, fd);
	close(fd);

	fd = open("test5.txt", O_RDONLY);
	assert(fd!= -1);

	read(fd, buf, strlen(str));
	close(fd);

	buf[strlen(str)] = '\0';
	assert(strcmp(buf, str) == 0);
}

int	main(void)
{
	test_putstr_fd_leading_trailing_whitespace();
	test_putstr_fd_empty_string();
	test_putstr_fd_only_whitespace();
	test_putstr_fd_long_string();
	test_putstr_fd_non_printable();

	printf("All tests passed!\n");
	return (0);
}
 */
