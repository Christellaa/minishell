/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 11:32:10 by cde-sous          #+#    #+#             */
/*   Updated: 2024/08/26 21:33:42 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// doesn't work for some ranges, possibly because of modulo bias

static unsigned int	g_state = 0;

#define MULTIPLIER 1103515245
#define INCREMENT 12345

// init random state
static void	init_rng(void)
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		fd = open("/dev/random", O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Error while opening file");
			return ;
		}
	}
	read(fd, &g_state, sizeof(g_state));
	close(fd);
	if (g_state == 0)
		g_state = 1;
}

// Generate the next random number
static unsigned int	next_rng(void)
{
	g_state = (g_state * MULTIPLIER + INCREMENT) % 2147483648;
	return (g_state);
}

// Generate a random number between min and max
unsigned int	ft_rand(unsigned int min, unsigned int max)
{
	unsigned int	range;
	unsigned int	treshold;
	unsigned int	random_value;

	if (g_state == 0)
		init_rng();
	range = max - min + 1;
	treshold = 2147483648 - 1 - ((2147483648 - 1) % range);
	while (1)
	{
		random_value = next_rng();
		if (random_value <= treshold)
			break ;
	}
	return (min + (random_value % range));
}
