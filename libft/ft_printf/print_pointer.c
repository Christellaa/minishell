/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous  <cde-sous@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:58:30 by cde-sous          #+#    #+#             */
/*   Updated: 2024/06/10 12:58:30 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *p)
{
	int	len;

	len = 0;
	if (!p)
		len += print_str("(nil)");
	else
	{
		len += print_str("0x");
		len += print_hex_long((unsigned long)p, 'x');
	}
	return (len);
}
