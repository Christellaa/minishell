/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:58:30 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 12:48:51 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	print_pointer_fd(int fd, void *p)
{
	int	len;

	len = 0;
	if (!p)
		len += print_str_fd(fd, "(nil)");
	else
	{
		len += print_str_fd(fd, "0x");
		len += print_hex_long_fd(fd, (unsigned long)p, 'x');
	}
	return (len);
}
