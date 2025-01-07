/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-sous <cde-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:16:12 by cde-sous          #+#    #+#             */
/*   Updated: 2025/01/07 16:49:10 by cde-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_value(char *equal_pos)
{
	char	*value;

	if (*(equal_pos + 1) != '\0')
		value = ft_strdup(equal_pos + 1);
	else
		value = ft_strdup("");
	if (!value)
		return (NULL);
	return (value);
}

t_token	*get_prev_token(t_token *prev, t_token *current)
{
	while (prev && prev->next != current)
		prev = prev->next;
	return (prev);
}

int	get_quoted_word_len(char *word)
{
	int	i;
	int	single_quote;
	int	double_quote;

	i = 1;
	single_quote = 0;
	double_quote = 0;
	while (word[i] && word[i] != word[0])
	{
		if (word[i] == SINGLE_QUOTE && !double_quote)
			single_quote = !single_quote;
		if (word[i] == DOUBLE_QUOTE && !single_quote)
			double_quote = !double_quote;
		i++;
	}
	if (word[i] == word[0])
		i++;
	return (i);
}

int	get_word_len(char *word, int flag)
{
	int	i;

	i = 0;
	if (word[0] == SINGLE_QUOTE || word[0] == DOUBLE_QUOTE)
		i = get_quoted_word_len(word);
	else
	{
		while (word[i])
		{
			if (word[i] == SINGLE_QUOTE || word[i] == DOUBLE_QUOTE)
				break ;
			if (flag == 1 && ft_isspace(word[i]))
				break ;
			if (flag == 2 && (word[i] == '<' || word[i] == '>'
					|| word[i] == '|'))
				break ;
			i++;
		}
	}
	return (i);
}
