/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:52:41 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:08 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Fills the first n bytes of the memory area pointed to by s with the constant
** byte c
** Returns a pointer to the memory area s
*/

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
	{
		*ptr = (char)c;
		ptr++;
		i++;
	}
	return (s);
}
