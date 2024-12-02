/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:26:43 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:38:00 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates memory for an array of nmemb elements of size bytes each and the 
** memory is set to zero
** If nmemb or size is 0, then malloc(0) is returned
** If nmemb is greater than SIZE_MAX / size, then NULL is returned
** Returns a pointer to the allocated memory, or NULL if the request fails
*/

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	buffer = malloc((nmemb * size));
	if (!buffer)
		return (NULL);
	ft_memset(buffer, 0, nmemb * size);
	return (buffer);
}
