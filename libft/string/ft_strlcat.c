/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:25:49 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:24 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Concatenate src to dst
** Returns the total length of the string created in dst (so the length of
** dst + src or siz + src if dst is shorter than siz)
*/

#include "../libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (siz > dst_len)
	{
		while (i < siz - 1 - dst_len && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
		return (dst_len + src_len);
	}
	return (siz + src_len);
}
