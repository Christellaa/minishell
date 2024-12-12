/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strepur.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 09:52:05 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/12 12:57:23 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

int	handle_spaces(char *str, int i, char *epur, int *idx)
{
	int	end_pos;

	end_pos = ft_strlen(str) - 1;
	if ((str[i] == ' ' || str[i] == '\t'))
	{
		if (i == 1 && (str[i - 1] == '\'' || str[i - 1] == '"'))
			i += skip_spaces(&str[i]);
		else
		{
			i += skip_spaces(&str[i]);
			if (i < end_pos)
				epur[(*idx)++] = ' ';
		}
	}
	else
		epur[(*idx)++] = str[i++];
	return (i);
}

char	*ft_strepur(char *str)
{
	char	*epur;
	int		i;
	int		idx;

	if (!str)
		return (NULL);
	epur = malloc(ft_strlen(str) + 1);
	if (!epur)
		return (NULL);
	i = skip_spaces(str);
	idx = 0;
	while (str[i])
	{
		i = handle_spaces(str, i, epur, &idx);
	}
	epur[idx] = '\0';
	return (epur);
}
