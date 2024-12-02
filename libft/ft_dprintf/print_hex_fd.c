/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:58:08 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 12:56:37 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	print_hex_fd(int fd, unsigned int nb, char current)
{
	int		len;
	char	*base;

	len = 0;
	if (current == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (nb >= 16)
	{
		len += print_hex_fd(fd, nb / 16, current);
		len += print_hex_fd(fd, nb % 16, current);
	}
	else
	{
		len += print_char_fd(fd, base[nb % 16]);
	}
	return (len);
}
