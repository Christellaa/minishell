/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:45:34 by cde-sous          #+#    #+#             */
/*   Updated: 2024/09/25 09:36:51 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates a new string and store the conversion of n to ASCII characters
** Negative numbers must be handled
** Returns the string representing the int, or NULL if the allocation fails
*/

#include "../libft.h"

static char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static int	count_digits(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter++;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

static void	reverse(char *s, int len, int is_negative)
{
	int		start;
	int		end;
	char	temp;

	if (is_negative == 1)
		start = 1;
	else
		start = 0;
	end = len - 1;
	while (start < end)
	{
		temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}

static char	*convert(int n, char *s)
{
	int	i;
	int	is_negative;

	i = 0;
	is_negative = 0;
	if (n == 0)
		return (ft_strcpy(s, "0"));
	if (n < 0)
	{
		is_negative = 1;
		s[i++] = '-';
		if (n == -2147483648)
		{
			return (ft_strcpy(s, "-2147483648"));
		}
		n = -n;
	}
	while (n > 0)
	{
		s[i++] = n % 10 + '0';
		n /= 10;
	}
	s[i] = '\0';
	reverse(s, i, is_negative);
	return (s);
}

char	*ft_itoa(int n)
{
	char	*to_ascii;

	to_ascii = malloc((count_digits(n) + 1) * sizeof(char));
	if (!to_ascii)
		return (NULL);
	convert(n, to_ascii);
	return (to_ascii);
}
