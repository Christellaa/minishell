/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:14:45 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:29 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Applies f to each character of s and stores the result in a new string
** Returns the string created from the successive applications of f, or NULL
** if the allocation fails
*/

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s2;

	i = 0;
	s2 = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = f(i, s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
