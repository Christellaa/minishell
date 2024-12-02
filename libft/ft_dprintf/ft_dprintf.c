/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 08:08:03 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 12:54:51 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static int	convert(char current, va_list ptr, int len, int fd)
{
	if (current == 's')
		len += print_str_fd(fd, va_arg(ptr, char *));
	else if (current == 'c')
		len += print_char_fd(fd, va_arg(ptr, int));
	else if (current == 'd' || current == 'i')
		len += print_int_fd(fd, va_arg(ptr, int));
	else if (current == 'u')
		len += print_unsigned_fd(fd, va_arg(ptr, unsigned int));
	else if (current == 'x' || current == 'X')
		len += print_hex_fd(fd, va_arg(ptr, unsigned int), current);
	else if (current == 'p')
		len += print_pointer_fd(fd, va_arg(ptr, void *));
	else if (current == '%')
		len += print_char_fd(fd, '%');
	else
		return (-1);
	return (len);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	const char	*current;
	int			len;
	va_list		ptr;
	int			i;

	current = format;
	len = 0;
	i = 0;
	va_start(ptr, format);
	while (current[i])
	{
		if (current[i] == '%')
			len = convert(current[++i], ptr, len, fd);
		else
			len += print_char_fd(fd, current[i]);
		if (current[i] != '\0')
			i++;
	}
	va_end(ptr);
	return (len);
}
