/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:28:56 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:38 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns a pointer to the last occurrence of the character c in the string s
** or NULL if the character is not found
** The terminating null byte is considered to be part of the string
*/

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	if (c == '\0')
		return ((char *)(s + ft_strlen(s)));
	return (NULL);
}
