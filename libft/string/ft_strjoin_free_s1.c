/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free_s1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:00:53 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/17 13:42:02 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

char	*ft_strjoin_free_s1(char *s1, char const *s2, char *ptr)
{
	char	*s3;
	char	*ptr3;
	char	*ptr1;

	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*s3));
	if (!s3)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	ptr3 = s3;
	if (s1)
	{
		ptr1 = s1;
		while (*ptr1)
			*ptr3++ = *ptr1++;
	}
	while (*s2)
		*ptr3++ = *s2++;
	*ptr3 = '\0';
	if (s1)
		free(s1);
	if (ptr)
		free(ptr);
	return (s3);
}
