/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:43:19 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:37:58 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Erase the first n bytes of the memory area pointed to by s
** by writing zeros to that area
** Return nothing
*/

#include "../libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptrchar;

	i = 0;
	ptrchar = (char *)s;
	while (i < n)
	{
		ptrchar[i] = '\0';
		i++;
	}
}
