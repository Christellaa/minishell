/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:57:36 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 12:48:55 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	print_int_fd(int fd, long long nb)
{
	int	len;

	len = 0;
	if (nb < 0)
	{
		len += print_char_fd(fd, '-');
		nb = -nb;
	}
	if (nb > 9)
	{
		len += print_int_fd(fd, nb / 10);
		len += print_int_fd(fd, nb % 10);
	}
	else
		len += print_char_fd(fd, nb + '0');
	return (len);
}
