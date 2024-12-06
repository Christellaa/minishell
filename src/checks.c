/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 15:56:41 by cde-sous          #+#    #+#             */
/*   Updated: 2024/12/06 16:43:15 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_forbidden_input(char *word)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 0;
	single_quote = 0;
	double_quote = 0;
	while (word[i])
	{
		if (word[i] == SINGLE_QUOTE && !double_quote)
			single_quote = !single_quote;
		else if (word[i] == DOUBLE_QUOTE && !single_quote)
			double_quote = !double_quote;
		else if (ft_strchr(FORBIDDEN_CHARS, word[i]) && !single_quote
			&& !double_quote)
			return (1);
		else if (word[i] == '|' && word[i + 1] == '|' && !single_quote
			&& !double_quote)
			return (1);
		else if (word[i] == '?' && i > 0 && word[i - 1] != '$' && !single_quote
				&& !double_quote) // if i = 0 && word[i] == '?' return 1
			return (1);
		i++;
	}
	return (0);
}
