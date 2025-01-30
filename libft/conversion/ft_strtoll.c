/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carzhang <carzhang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:41:19 by carzhang          #+#    #+#             */
/*   Updated: 2025/01/30 16:17:18 by carzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

const char	*handle_sign(const char *nptr, int *sign)
{
	*sign = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			*sign = -1;
		nptr++;
	}
	return (nptr);
}

const char	*handle_base(const char *nptr, int *base)
{
	if (*base == 0)
	{
		if (*nptr == '0' && (*(nptr + 1) == 'x' || *(nptr + 1) == 'X'))
		{
			*base = 16;
			nptr += 2;
		}
	}
	else if (*nptr == '0')
	{
		*base = 8;
		nptr++;
	}
	else
		*base = 10;
	return (nptr);
}

int	get_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

const char	*convert_digits(const char *nptr, long long *res, int base)
{
	int	digit;

	digit = get_digit(*nptr);
	while (digit != -1 && digit < base)
	{
		if (*res > (LLONG_MAX - digit) / base)
		{
			errno = ERANGE;
			*res = LLONG_MAX;
			return (nptr);
		}
		*res = (*res * base) + digit;
		nptr++;
		digit = get_digit(*nptr);
	}
	return (nptr);
}

long long	ft_strtoll(const char *nptr, char **endptr, int base)
{
	long long	res;
	int			sign;

	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	nptr = handle_sign(nptr, &sign);
	nptr = handle_base(nptr, &base);
	res = 0;
	nptr = convert_digits(nptr, &res, base);
	if (errno == ERANGE && sign == -1)
		return (LLONG_MIN);
	if (endptr)
		*endptr = (char *)nptr;
	return (sign * res);
}
