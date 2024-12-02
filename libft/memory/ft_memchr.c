/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:44:02 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:02 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Checks for the first occurrence of c (converted to an unsigned char) in s
** until n bytes
** Returns a pointer to the byte in s that has the value c, or NULL if not found
*/

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptrs;
	size_t				i;

	ptrs = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptrs[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	return (NULL);
}
