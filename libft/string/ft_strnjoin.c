/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:21:53 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/05 16:20:02 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	size_t	s1_len;
	size_t	i;
	char	*s3;

	s1_len = ft_strlen(s1);
	s3 = malloc(s1_len + n + 1);
	if (!s3)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (*s1)
			s3[i++] = *(s1++);
	}
	if (s2)
	{
		while (*s2 && i - s1_len < n)
			s3[i++] = *(s2++);
	}
	s3[i] = '\0';
	return (s3);
}
