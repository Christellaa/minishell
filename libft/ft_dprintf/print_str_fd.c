/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:56:41 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/22 12:48:49 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

int	print_str_fd(int fd, char *s)
{
	int	len;

	len = 0;
	if (!s)
	{
		return (len += write(fd, "(null)", 6));
	}
	while (*s)
		len += write(fd, s++, 1);
	return (len);
}
