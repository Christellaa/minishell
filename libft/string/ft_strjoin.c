/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:26:46 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:22 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates a new string, which is the concatenation of s1 and s2
** Returns the new string, or NULL if the allocation fails
*/

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		i;
	int		j;
	char	*buffer;

	len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	buffer = malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (s1[i])
	{
		buffer[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		buffer[i + j] = s2[j];
		j++;
	}
	buffer[i + j] = '\0';
	return (buffer);
}
