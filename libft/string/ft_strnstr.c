/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:20:55 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:36 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Checks the first occurrence of little (needle) in big (haystack), up to len
** Characters after null terminator are not checked
** Returns a pointer to the first occurrence of needle in haystack
** or big if little is empty, or NULL if little is not found in big
*/

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			if (!big[i + j] && !little[j])
				return ((char *)&big[i]);
			j++;
		}
		if (!little[j])
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
