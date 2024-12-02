/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous  <cde-sous@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:57:53 by cde-sous          #+#    #+#             */
/*   Updated: 2024/06/10 12:57:53 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb > 9)
	{
		len += print_unsigned(nb / 10);
		len += print_unsigned(nb % 10);
	}
	else
	{
		len += print_char(nb + '0');
	}
	return (len);
}
