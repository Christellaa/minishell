/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:17:55 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:06 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies n bytes from memory area src to memory area dest
** Memory areas may overlap
** Returns a pointer to dest
*/

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*ptrdest;
	const char	*ptrsrc;

	ptrdest = (char *)dest;
	ptrsrc = (const char *)src;
	if (!dest && !src)
		return (dest);
	if (src >= dest)
	{
		ft_memcpy(ptrdest, src, n);
	}
	if (dest > src)
	{
		while (n-- > 0)
		{
			ptrdest[n] = ptrsrc[n];
		}
	}
	return (dest);
}
